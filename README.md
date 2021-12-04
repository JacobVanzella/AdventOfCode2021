# Advent of Code 2021
## Solutions by Jacob Vanzella - Written in C++

This repository contains my solutions for the 2021 [Advent of Code](https://adventofcode.com/) coding challenge in C++.

## Fundamental Concepts

## Day 1:
### Part 1
The intro puzzle is as simple as a counting while loop, nothing special here.
### Part 2
Part two isn't much more difficult than part one, but there is a cute technique to store these rotating values. By using an array of length N where N is the window size, we can use an index mod N to track a rotating position inside the array. This means we don't need to shift the values on each iteration.

## Day 2:
### Part 1 & 2
Very little to talk about here, the only cute trick I used is to compare the first character as opposed to the entire direction string.

## Day 3:
### Part 1
By counting the frequency of occurences of the number 1 in each position we generate a representation of Gamma. For each digit greater than or equal to 4 replace with a 1, else a 0, gives the binary representation of Gamma. This is a big endian binary number who's complement is epsilon. The rest follows simply.

e.g.
Counts[digits] = {7, 5, 8, 7, 5}

Gamma = 10110

Epsilon = ~Gamma = 01001