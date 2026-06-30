#!/usr/bin/env python3
"""Regenerate the auto-updated stats section of README.md.

Counts solved problems (*.cpp files) per source and per CSES category, pulls a
couple of numbers out of git history, and rewrites everything between the
<!-- STATS:START --> and <!-- STATS:END --> markers in README.md.

Safe to run by hand on any OS (`python scripts/update_readme_stats.py`); it is
also run automatically by .github/workflows/update-stats.yml on every push.
"""
from __future__ import annotations

import subprocess
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
README = ROOT / "README.md"
START = "<!-- STATS:START -->"
END = "<!-- STATS:END -->"

# Directory for reusable templates (counted separately, not as "problems").
TEMPLATES_DIR = "templates"

# Each source maps to one or more top-level folders, plus a flavour blurb.
# Order here is irrelevant; the table is sorted by problem count, descending.
SOURCES = [
    ("⚔️ Codeforces", ["codeforces"],
     "Rounds, Educational & ICPC regionals — the daily grind"),
    ("🇫🇮 CSES", ["CSES"],
     "The classic problem set, one category at a time (see below)"),
    ("🏯 ZeroJudge", ["zerojudge"],
     "Taiwan's finest gauntlet of WA verdicts"),
    ("🎓 APCS", ["APCS", "APCS_Simulation"],
     "Real exam past papers + simulations"),
    ("🏆 YTP", ["YTP"],
     "Preliminary, Online & Final contests across the years"),
    ("🟧 LeetCode", ["leetcode"],
     "For when I want to feel briefly competent"),
    ("📚 I2CP", ["2023_I2CP_PreTraining_Autumn", "2025_I2CP"],
     "Pre-training & coursework grind"),
    ("🐄 USACO", ["USACO"],
     "The cows and I are still negotiating"),
]

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


def build_section() -> str:
    # --- per-source counts ---
    source_rows = []
    total_solved = 0
    for label, folders, blurb in SOURCES:
        n = sum(count_cpp(f) for f in folders)
        if n == 0:
            continue
        total_solved += n
        source_rows.append((label, n, blurb))
    source_rows.sort(key=lambda r: r[1], reverse=True)

    templates_n = count_cpp(TEMPLATES_DIR)
    total_cpp = total_solved + templates_n

    # --- CSES per-category ---
    cses_rows = []
    if CSES_DIR.exists():
        for sub in sorted(CSES_DIR.iterdir()):
            if sub.is_dir():
                n = sum(1 for _ in sub.rglob("*.cpp"))
                if n:
                    cses_rows.append((pretty(sub.name), n))
        cses_rows.sort(key=lambda r: r[1], reverse=True)

    # --- git stats ---
    commits = git("rev-list", "--count", "HEAD") or "?"
    first_date = git("log", "--reverse", "--format=%ad", "--date=short")
    first_date = first_date.splitlines()[0] if first_date else "?"
    today = datetime.now(timezone.utc).strftime("%Y-%m-%d")

    # round problems down to nearest 10 for the headline "X+" figure
    headline = (total_solved // 10) * 10

    lines: list[str] = []
    lines.append("## The Damage So Far 📊")
    lines.append("")
    lines.append("> Numbers don't lie (the code, however, frequently does).")
    lines.append("")
    lines.append("| Stat | Value |")
    lines.append("|------|------:|")
    lines.append(f"| 🧩 Problems suffered through | **{headline}+** |")
    lines.append(f"| 📝 Total `.cpp` files (incl. templates) | **{total_cpp}** |")
    lines.append(f"| 💾 Commits of regret | **{commits}** |")
    lines.append(f"| 📅 In the trenches since | **{first_date}** |")
    lines.append(f"| 🗂️ Judges & contest archives | **{len(source_rows)}** |")
    lines.append(f"| 🛠️ Battle-tested templates | **{templates_n}** |")
    lines.append("")
    lines.append("## Where the Suffering Comes From 🌍")
    lines.append("")
    lines.append("A curated tour of the online judges and contest archives that "
                 "have personally wronged me:")
    lines.append("")
    lines.append("| Source | Solved | What it is |")
    lines.append("|--------|-------:|------------|")
    for label, n, blurb in source_rows:
        lines.append(f"| {label} | {n} | {blurb} |")
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
                lines.append(f"| {left[0]} | {left[1]} | {right[0]} | {right[1]} |")
            else:
                lines.append(f"| {left[0]} | {left[1]} | | |")
        lines.append("")

    lines.append("## The Arsenal 🛠️")
    lines.append("")
    lines.append(f"{templates_n} templates I copy-paste at 3 AM and pray they "
                 "still work — segment trees, BITs, treaps, tries, string "
                 "algorithms, geometry, and more.")
    lines.append("")
    lines.append(f"<sub>📈 Auto-updated on every push · last refreshed "
                 f"{today} (UTC)</sub>")

    return "\n".join(lines)


def main() -> int:
    text = README.read_text(encoding="utf-8")
    if START not in text or END not in text:
        raise SystemExit(
            f"Markers {START} / {END} not found in README.md — cannot update."
        )
    before, rest = text.split(START, 1)
    _, after = rest.split(END, 1)
    new_text = f"{before}{START}\n{build_section()}\n{END}{after}"
    if new_text != text:
        README.write_text(new_text, encoding="utf-8")
        print("README.md stats updated.")
    else:
        print("README.md already up to date.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
