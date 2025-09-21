#!/usr/bin/env bash
set -e

# compile your programs first:
# g++ -std=gnu17 -O2 -pipe -o correct correct.cpp
# g++ -std=gnu17 -O2 -pipe -o mine mine.cpp

GEN=./gen
CORRECT=./correct
MINE=./mine

# params
Tcases=1        # how many testcases per generation file (you can set >1)
NMAX=200        # max n per test
MODE=0          # generator mode: 0=balanced, 1=edge heavy

# infinite loop until mismatch
iter=0
while true; do
  iter=$((iter+1))
  $GEN $Tcases $NMAX $RANDOM $MODE > in.txt
  $CORRECT < in.txt > out_corr.txt
  $MINE    < in.txt > out_mine.txt

  if ! diff -u out_corr.txt out_mine.txt > diff.txt; then
    echo "Mismatch found on iteration $iter"
    echo "====== INPUT ======"
    cat in.txt
    echo "====== CORRECT ======"
    cat out_corr.txt
    echo "====== MINE ======"
    cat out_mine.txt
    echo "====== DIFF ======"
    sed -n '1,200p' diff.txt
    exit 0
  fi

  if (( iter % 200 == 0 )); then
    echo "Passed $iter tests..."
  fi
done
