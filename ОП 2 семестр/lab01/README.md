# Lab 1 — Pointers and 1D Dynamic Arrays (C++)

This repository contains a C++ solution for a lab on pointers and one-dimensional dynamic arrays.
The program generates a dynamic array using random integers and allows the user to apply one of the following operations.

## Features (Menu)

1. Remove all negative two-digit elements from the array (range: `[-99; -10]`)
2. Add `K` prime numbers to the beginning of the array (`K` is entered from the keyboard)
3. Insert `0` after every even element in the array

## Build & Run (macOS/Linux)

```bash
cmake -S . -B build
cmake --build build
./build/app
