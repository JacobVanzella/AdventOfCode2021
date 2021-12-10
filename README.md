# Advent of Code 2021
## Solutions by Jacob Vanzella - Written in C++

This repository contains my solutions for the 2021 [Advent of Code](https://adventofcode.com/) coding challenge in C++. Days are split into two parts, each part has its own .cpp file. Parts with a BONUS.cpp are ones I revisited and re-wrote because I thought of a more efficient or beautiful solution after the fact.

## Fundamental Concepts

## Day 1:
### Part 1
The intro puzzle is as simple as a counting while loop, nothing special here.
### Part 2
Part two isn't much more difficult than part one, but there is a cute technique to store these rotating values. By using an array of length `N` where `N` is the window size, we can use an index mod `N` to track a rotating position inside the array. This means we don't need to shift the values on each iteration.

## Day 2:
### Part 1 & 2
Very little to talk about here, the only cute trick I used is to compare the first character as opposed to the entire direction string.

## Day 3:
### Part 1
By counting the frequency of occurences of the number 1 in each position we generate a representation of Gamma. For each digit greater than or equal to 1/2 the number of elements replace with a 1, else a 0, gives the binary representation of Gamma. This is a big endian binary number who's complement is Epsilon. The rest follows simply.

e.g.
```
Counts[digits] = {7, 5, 8, 7, 5}
Gamma = 10110
Epsilon = ~Gamma = 01001
```

### Part 2
Now here some interesting work got done, and by interesting I mean I think I overcomplicated the solution. The naive solution would be to calculate frequency, eliminate elements not fitting the rule, recalculate frequency, etc. etc. Without busting out a pen and paper I believe this would reduce down to a `O(N*M!)` complexity where `N` is the number of elements and `M` is their length. To avoid this lame complexity I instead decided to use a trie. Construction of the trie should be `O(N*M)` and searching the trie is `O(M)`. Each parent contains the number of 0 children or 1 children which takes care of the frequency calculation.

## Day 4:
### Part 1 & 2
Nothing too exciting here. I had considered using a hashmap solution, but I decided to save myself a little thinking and went the brute force route of checking every value on each board until a/last winner was found.

## Day 5:
### Part 1 & 2
Nothing fancy, just careful attention to direction. Only challenging part is keeping track of which way is up and down in part 2.

## Day 6:
### Part 1 & 2
Again, nothing fancy. Create an array of integers 9 long and keep track of the number of fish where the index of the array is the fishes internal counter. There is a cute trick you could do with a rotating sentinel value, and it would be worth it if you had to keep track of many numbers, but with so few it's easier to just write a simple array shifting algorithm. For part 2 make sure to use `long long`.

## Day 7:
### Part 1
(Note: Apparently GitHub doesn't support LaTeX? Leaving the equations in protest.)

<b>What have:</b> A collection of points $P_i = V$ where $V$ is the value (absolute position) of the point. There can be multiple points with a single value. The number of points with a given value is the cardinality of the point $|P_i|$

<b>What we want:</b> To move all points such that their value is equal.

<b>What it costs:</b> Cost of movement $C = |V_{dest} - V_{p_i}| \times |P_i|$

### Part 2
The problem is fundamentally the same, only an adjustment to the cost calculation needs to be made.

Cost of movement $C = \Sigma_{I=0}^{|V_{dest} - V_{p_i}|}(I) \times |P_i|$

### Part 2 BONUS
In my initial solve of parts 1 and 2 I used a brute force approach with a small optimization using the monotanicity of the function to the left and right of the solution. This optimization however doesn't really improve the worst case performance which is O(n<sup>3</sup>) for part 2. After some thought I realized that a factor of n could be eliminated in part 2 by using the [arithmetic progression formula](https://en.wikipedia.org/wiki/Arithmetic_progression). Shortly after I realized that another factor of n could be reduced to lg(n) by using a binary search style gradient descent. Right before implementing this improvement however I mentioned this approach to a friend and he blew my solution out of the water. Find the mean value of the points, this value is ±1 from the minimum solution. Then just test the integer values to the either side of the mean. This results in a O(n) running time! Wow. Excellent insight Phil.

Resuls of a timing test, the proof is in the pudding.
```
time ./7_2

Ans. 96744904 , Dest: 475

real    0m2.195s
user    0m2.189s
sys     0m0.000s
--------------------------
time ./7_2_BONUS

Ans. 96744904 , Dest: 475

real    0m0.009s
user    0m0.008s
sys     0m0.000s
```

## Day 8:
