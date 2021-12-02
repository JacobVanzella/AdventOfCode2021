#!/bin/bash

# Create files and directories
for i in {1..25}
do
	mkdir "Day$(printf '%d' "$i")"
	cd "Day$(printf '%d' "$i")"
	
	touch "$(printf '%d' "$i")_1.cpp"
	touch "$(printf '%d' "$i")_2.cpp"
	touch input.txt
	touch test.txt
	
	cd ..
done
