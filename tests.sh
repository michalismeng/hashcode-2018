#!/bin/sh
rm a.out
g++ -O3 -Wall debian.cpp
./a.out < a_example.in > a_example.out
./a.out < b_should_be_easy.in > b_should_be_easy.out
./a.out < c_no_hurry.in > c_no_hurry.out
./a.out < d_metropolis.in > d_metropolis.out
./a.out < e_high_bonus.in > e_high_bonus.out
