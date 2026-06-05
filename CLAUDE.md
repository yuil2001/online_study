# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A collection of three competitive programming C++ console applications, built with Visual Studio 2015 (MSVC v140, Win32/x64). Each problem lives in its own subdirectory with its own `.sln` and `.vcxproj` files.

## Building

These projects use MSBuild (Visual Studio 2015). On Linux/macOS, each `.cpp` can be compiled directly with g++ since only standard libraries are used (no Windows-specific APIs except `_tmain` in LineFriends):

```bash
# Rollercoaster
g++ -std=c++11 -o rollercoaster rollercoaster/rollercoaster.cpp

# Helicopter
g++ -std=c++11 -o helicopter Helicopter/Helicopter/Helicopter.cpp

# LineFriends (requires renaming _tmain → main, or -D_TCHAR_IS_CHAR)
g++ -std=c++11 -D_tmain=main -D_TCHAR=char -o linefriends LineFriends/LineFriends/LineFriends.cpp
```

On Windows, open the `.sln` file in Visual Studio and build normally.

## Running and Testing

### Rollercoaster

Has a `#define TEST` block at the top of `rollercoaster.cpp` that hardcodes a 4×4 grid — the program uses this data automatically when compiled with `TEST` defined. To use stdin input, comment out `#define TEST` and pipe your input:

```bash
echo "4 4\n5 1 3 3\n4 0 1 1\n2 1 2 0\n2 2 1 2" | ./rollercoaster
```

### Helicopter and LineFriends

Both read from stdin. Both have `input.txt` files in their project directories for quick testing:

```bash
./helicopter < Helicopter/Helicopter/input.txt
./linefriends < LineFriends/LineFriends/input.txt
```

There is no automated test framework — correctness is verified by comparing stdout against expected output manually.

## Architecture

### Rollercoaster (`rollercoaster/rollercoaster.cpp`)

Finds the path from `(0,0)` to `(r-1, c-1)` in a 2D grid that maximizes the sum of `happy_value` along the way.

- **Data model**: A flat `vector<node>` indexed by `row * r + col`. Each `node` stores direction flags (`up/right/left/down`), `prev_r/prev_c` for backtracking, `is_aready_sum` to avoid revisiting, and `happy_value`.
- **Algorithm**: Iterative DFS implemented as a state machine in `search()`. At each cell the four direction flags act as a "which moves have I tried from here" record. When all four directions are exhausted, the node backtracks via `prev_r/prev_c`. The global `max_sum` / `max_sum_path` are updated whenever the destination is reached.
- **Note**: `clear_history()` contains a `return` as its first statement — it is intentionally a no-op; direction flags are never reset during a run.

### Helicopter (`Helicopter/Helicopter/Helicopter.cpp`)

Calculates the minimum travel distance for a helicopter following a lower boundary path, where one "division" (a pair of segments between even-indexed lower-boundary points) is replaced with its direct Euclidean distance instead of Manhattan.

- **Data model**: `vector<Point>` for upper (`upper_bound`) and lower (`down_bound`) boundary coordinates. Upper boundary is read but currently unused.
- **Algorithm**: Groups consecutive lower-boundary points into pairs; calculates Manhattan length for each division (pairs of segments). Stores all division lengths in a `multimap` keyed by length. Removes the longest division from the total and replaces it with the Euclidean distance between the two flanking even-indexed points.

### LineFriends (`LineFriends/LineFriends/LineFriends.cpp`)

Given line segments on a number line, two lines are "friends" if their intervals overlap. For each query `(a, b)`, finds the minimum degree of separation between line `a` and line `b` through transitive friend relationships (like degrees in a social graph). Returns `-1` if unreachable.

- **Data model**: `vector<Line>` (each with `_left`, `_right`) and `vector<Question>` (each with `_a`, `_b`). Query indices are **1-based in input** and converted to 0-based internally (`_a--; _b--`).
- **Algorithm**: `Question::Solve` does a BFS where each "level" is one friendship hop. `isFriend` checks interval overlap with two conditions (a contains b's left endpoint, or a contains b's right endpoint). `SolveSub` is a recursive BFS expansion tracking visited nodes in a `set<int> prev_a` to avoid cycles.
- **Entry point**: Uses `_tmain(int argc, _TCHAR* argv[])` — the Windows TCHAR entry point.

## Conventions

- Each project's main source file is the only file that matters; `stdafx.h/cpp` are boilerplate precompiled-header stubs from Visual Studio's project wizard.
- Array indexing into the flat node grid in rollercoaster uses `row * r + col` (not `row * c + col`) — this is a latent bug to be aware of when `r ≠ c`.
- Input validation is done with early returns and `cout` error messages (not exceptions or `cerr`).
