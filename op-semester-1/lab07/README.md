# Lab 07 — Strings (menu program)

Console program for working with a text line (C-style `char[]`) using a simple menu.

## Features
- Count words in the line
- Find the length of the shortest word
- Find the length of the longest word
- Change the current line
- Pause after each operation (“Press Enter to continue...”)

## Implementation notes
- The program scans the string symbol-by-symbol.
- A “word” is a sequence of non-whitespace characters.
- `shortestWordLength` / `longestWordLength` use the same pattern:
  - accumulate current word length
  - on whitespace (word end) update min/max
  - handle the final word after the loop

## Build & Run
Example (g++):
```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o lab07
./lab07