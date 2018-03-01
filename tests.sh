#!/bin/sh
rm a.out
g++ -O3 -Wall debian.cpp
./a.out < ~/Downloads/a_example.in > a_example.out
./a.out < ~/Downloads/b_should_be_easy.in > b_should_be_easy.out
./a.out < ~/Downloads/c_no_hurry.in > c_no_hurry.out
./a.out < ~/Downloads/d_metropolis.in > d_metropolis.out
./a.out < ~/Downloads/e_high_bonus.in > e_high_bonus.out

