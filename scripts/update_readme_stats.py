#!/usr/bin/env python3
"""Regenerate the auto-updated stats section of README.md and stats.json.

Counts solved problems (*.cpp files) per source and per CSES category, pulls a
couple of numbers out of git history, and rewrites everything between the
<!-- STATS:START --> and <!-- STATS:END --> markers in README.md.

The same numbers — plus a daily activity map and a recent-solves feed — go to
stats.json at the repo root, which https://beansamuel.github.io fetches to
render its Competitive Programming page. Keep the keys in sync with
src/data/cpStatsSnapshot.js over there if you change the shape.

Safe to run by hand on any OS (`python scripts/update_readme_stats.py`); it is
also run automatically by .github/workflows/update-stats.yml on every push.
"""
from __future__ import annotations

import json
import subprocess
from dataclasses import dataclass
from datetime import date, datetime, timedelta, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
README = ROOT / "README.md"
STATS_JSON = ROOT / "stats.json"
START = "<!-- STATS:START -->"
END = "<!-- STATS:END -->"

# Directory for reusable templates (counted separately, not as "problems").
TEMPLATES_DIR = "templates"

# How many recent solves to expose in stats.json.
RECENT_LIMIT = 24


@dataclass(frozen=True)
class Source:
    key: str          # stable id the website keys off; don't rename casually
    emoji: str
    name: str
    folders: tuple[str, ...]
    blurb: str
    url: str


# Each source maps to one or more top-level folders, plus a flavour blurb.
# Order here is irrelevant; the table is sorted by problem count, descending.
SOURCES = [
    Source("codeforces", "⚔️", "Codeforces", ("codeforces",),
           "Rounds, Educational & ICPC regionals — the daily grind",
           "https://codeforces.com/"),
    Source("cses", "🇫🇮", "CSES", ("CSES",),
           "The classic problem set, one category at a time (see below)",
           "https://cses.fi/problemset/"),
    Source("zerojudge", "🏯", "ZeroJudge", ("zerojudge",),
           "Taiwan's finest gauntlet of WA verdicts",
           "https://zerojudge.tw/"),
    Source("apcs", "🎓", "APCS", ("APCS", "APCS_Simulation"),
           "Real exam past papers + simulations",
           "https://apcs.csie.ntnu.edu.tw/"),
    Source("ytp", "🏆", "YTP", ("YTP",),
           "Preliminary, Online & Final contests across the years",
           "https://ytp.nchu.edu.tw/"),
    Source("leetcode", "🟧", "LeetCode", ("leetcode",),
           "For when I want to feel briefly competent",
           "https://leetcode.com/"),
    Source("i2cp", "📚", "I2CP", ("2023_I2CP_PreTraining_Autumn", "2025_I2CP"),
           "Pre-training & coursework grind",
           "https://sites.google.com/view/i2cp/"),
    Source("usaco", "🐄", "USACO", ("USACO",),
           "The cows and I are still negotiating",
           "http://www.usaco.org/"),
]

# Top-level folder -> source, for classifying paths pulled out of git history.
FOLDER_TO_SOURCE = {f: s for s in SOURCES for f in s.folders}

# Nicer labels for CSES sub-folders; anything not listed falls back to the
# folder name with underscores turned into spaces.
CSES_DIR = ROOT / "CSES"


def count_cpp(folder: str) -> int:
    """Count *.cpp files under a top-level folder (recursively)."""
    base = ROOT / folder
    if not base.exists():
        return 0
    return sum(1 for _ in base.rglob("*.cpp"))


def git(*args: str) -> str:
    try:
        return subprocess.check_output(
            ["git", *args], cwd=ROOT, text=True, stderr=subprocess.DEVNULL
        ).strip()
    except Exception:
        return ""


def pretty(name: str) -> str:
    return name.replace("_", " ")


def solve_log() -> list[tuple[str, str, list[str]]]:
    """Return [(sha, YYYY-MM-DD, [added .cpp paths])], newest commit first.

    Keys off file *additions* rather than commit messages, so the activity map
    tracks problems actually solved rather than how often git got touched.
    """
    raw = git(
        "log", "--diff-filter=A", "--name-only", "--date=short",
        "--format=__C__%H|%ad", "--", "*.cpp",
    )
    entries: list[tuple[str, str, list[str]]] = []
    sha = day = ""
    files: list[str] = []
    for line in raw.splitlines():
        if line.startswith("__C__"):
            if sha and files:
                entries.append((sha, day, files))
            sha, _, day = line[len("__C__"):].partition("|")
            files = []
        elif line.strip():
            files.append(line.strip())
    if sha and files:
        entries.append((sha, day, files))
    return entries


def classify(path: str) -> tuple[Source, str] | None:
    """Map a repo path to (source, category); None if it isn't a problem file."""
    parts = Path(path).parts
    if len(parts) < 2:
        return None
    source = FOLDER_TO_SOURCE.get(parts[0])
    if source is None:
        return None
    # Everything between the source folder and the file names the category.
    category = pretty("/".join(parts[1:-1])) if len(parts) > 2 else source.name
    return source, category


def streaks(days: set[str]) -> tuple[int, int]:
    """Return (current, longest) run of consecutive days with a solve."""
    if not days:
        return 0, 0
    parsed = sorted(date.fromisoformat(d) for d in days)

    longest = run = 1
    for prev, cur in zip(parsed, parsed[1:]):
        run = run + 1 if cur - prev == timedelta(days=1) else 1
        longest = max(longest, run)

    # A streak only counts as current if it reached today or yesterday.
    today = datetime.now(timezone.utc).date()
    if parsed[-1] < today - timedelta(days=1):
        return 0, longest
    current, cursor = 1, parsed[-1]
    for day in reversed(parsed[:-1]):
        if cursor - day == timedelta(days=1):
            current += 1
            cursor = day
        else:
            break
    return current, longest


def collect() -> dict:
    """Gather every number README.md and the website need."""
    # --- per-source counts ---
    source_rows = []
    total_solved = 0
    for s in SOURCES:
        n = sum(count_cpp(f) for f in s.folders)
        if n == 0:
            continue
        total_solved += n
        source_rows.append({
            "key": s.key, "emoji": s.emoji, "name": s.name,
            "count": n, "blurb": s.blurb, "url": s.url,
        })
    source_rows.sort(key=lambda r: r["count"], reverse=True)

    templates_n = count_cpp(TEMPLATES_DIR)

    # --- CSES per-category ---
    cses_rows = []
    if CSES_DIR.exists():
        for sub in sorted(CSES_DIR.iterdir()):
            if sub.is_dir():
                n = sum(1 for _ in sub.rglob("*.cpp"))
                if n:
                    cses_rows.append({"name": pretty(sub.name), "count": n})
        cses_rows.sort(key=lambda r: r["count"], reverse=True)

    # --- git-derived history ---
    activity: dict[str, int] = {}
    recent: list[dict] = []
    for sha, day, files in solve_log():
        for path in files:
            hit = classify(path)
            if hit is None:
                continue
            source, category = hit
            activity[day] = activity.get(day, 0) + 1
            if len(recent) < RECENT_LIMIT:
                recent.append({
                    "date": day,
                    "sha": sha[:7],
                    "source": source.key,
                    "sourceName": source.name,
                    "emoji": source.emoji,
                    "category": category,
                    "problem": Path(path).stem,
                    "path": path,
                })

    commits = git("rev-list", "--count", "HEAD")
    first_date = git("log", "--reverse", "--format=%ad", "--date=short")
    first_date = first_date.splitlines()[0] if first_date else "?"
    current_streak, longest_streak = streaks(set(activity))

    return {
        "repo": "BeanSamuel/cpp_practice",
        # Date, not timestamp: a full clock would rewrite stats.json on every
        # push and bury the repo in no-op "auto-update" commits.
        "generatedAt": datetime.now(timezone.utc).strftime("%Y-%m-%d"),
        "totals": {
            # round problems down to nearest 10 for the headline "X+" figure
            "headline": (total_solved // 10) * 10,
            "problems": total_solved,
            "cppFiles": total_solved + templates_n,
            "templates": templates_n,
            "commits": int(commits) if commits.isdigit() else 0,
            "sourceCount": len(source_rows),
            "firstDate": first_date,
            "activeDays": len(activity),
            "currentStreak": current_streak,
            "longestStreak": longest_streak,
        },
        "sources": source_rows,
        "cses": {"total": sum(r["count"] for r in cses_rows),
                 "categories": cses_rows},
        "activity": dict(sorted(activity.items())),
        "recent": recent,
    }


def build_section(stats: dict) -> str:
    totals = stats["totals"]
    source_rows = stats["sources"]
    cses_rows = stats["cses"]["categories"]
    templates_n = totals["templates"]

    lines: list[str] = []
    lines.append("## The Damage So Far 📊")
    lines.append("")
    lines.append("> Numbers don't lie (the code, however, frequently does).")
    lines.append("")
    lines.append("| Stat | Value |")
    lines.append("|------|------:|")
    lines.append(f"| 🧩 Problems suffered through | **{totals['headline']}+** |")
    lines.append(f"| 📝 Total `.cpp` files (incl. templates) | **{totals['cppFiles']}** |")
    lines.append(f"| 💾 Commits of regret | **{totals['commits']}** |")
    lines.append(f"| 📅 In the trenches since | **{totals['firstDate']}** |")
    lines.append(f"| 🗂️ Judges & contest archives | **{totals['sourceCount']}** |")
    lines.append(f"| 🛠️ Battle-tested templates | **{templates_n}** |")
    lines.append("")
    lines.append("## Where the Suffering Comes From 🌍")
    lines.append("")
    lines.append("A curated tour of the online judges and contest archives that "
                 "have personally wronged me:")
    lines.append("")
    lines.append("| Source | Solved | What it is |")
    lines.append("|--------|-------:|------------|")
    for row in source_rows:
        lines.append(f"| {row['emoji']} {row['name']} | {row['count']} | {row['blurb']} |")
    lines.append("")

    if cses_rows:
        lines.append("### CSES Breakdown 🇫🇮")
        lines.append("")
        lines.append("Because finishing the whole set is a personality trait "
                     "I'm *aspiring* to:")
        lines.append("")
        lines.append("| Category | ✓ | Category | ✓ |")
        lines.append("|----------|--:|----------|--:|")
        # lay categories out two-per-row
        for i in range(0, len(cses_rows), 2):
            left = cses_rows[i]
            if i + 1 < len(cses_rows):
                right = cses_rows[i + 1]
                lines.append(f"| {left['name']} | {left['count']} | {right['name']} | {right['count']} |")
            else:
                lines.append(f"| {left['name']} | {left['count']} | | |")
        lines.append("")

    lines.append("## The Arsenal 🛠️")
    lines.append("")
    lines.append(f"{templates_n} templates I copy-paste at 3 AM and pray they "
                 "still work — segment trees, BITs, treaps, tries, string "
                 "algorithms, geometry, and more.")
    lines.append("")
    lines.append(f"<sub>📈 Auto-updated on every push · last refreshed "
                 f"{stats['generatedAt']} (UTC)</sub>")

    return "\n".join(lines)


def write_readme(stats: dict) -> None:
    text = README.read_text(encoding="utf-8")
    if START not in text or END not in text:
        raise SystemExit(
            f"Markers {START} / {END} not found in README.md — cannot update."
        )
    before, rest = text.split(START, 1)
    _, after = rest.split(END, 1)
    new_text = f"{before}{START}\n{build_section(stats)}\n{END}{after}"
    if new_text != text:
        README.write_text(new_text, encoding="utf-8")
        print("README.md stats updated.")
    else:
        print("README.md already up to date.")


def write_json(stats: dict) -> None:
    payload = json.dumps(stats, indent=2, ensure_ascii=False) + "\n"
    if not STATS_JSON.exists() or STATS_JSON.read_text(encoding="utf-8") != payload:
        STATS_JSON.write_text(payload, encoding="utf-8")
        print("stats.json updated.")
    else:
        print("stats.json already up to date.")


def main() -> int:
    stats = collect()
    write_readme(stats)
    write_json(stats)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
