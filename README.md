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
### Part 2
Now here some interesting work got done, and by interesting I mean I think I overcomplicated the solution. The naive solution would be to calculate frequency, eliminate elements not fitting the rule, recalculate frequency, etc. etc. Without busting out a pen and paper I believe this would reduce down to a O(N\*M!) complexity where N is the number of elements and M is their length. To avoid this lame complexity I instead decided to use a Huffman tree. Construction of the tree should be O(N\*M\) and searching the tree is O(M). Each parent contains the number of 0 children or 1 children which takes care of the frequency calculation.