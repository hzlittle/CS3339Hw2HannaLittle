# fp-overflow-checker-mzj21
Teammembers: Hanna Little-Neuhaus mzj21

This program checks if a number and the increment you want to apply to it might have overflow. It
tells you if it does or not, then if not tells you the smallest number you can increment it by in 
base 10 and IEEE format.

INCLUDES:
#include <iostream>
#include <iomanip>
#include <cstdlib> //for stof
#include <climits> //for INT_MAX, INT_MIN
#include <cmath> //for pow
#include <bitset>   // for bitset
using namespace std;

Requires:
-C++11 or later
-Standard C++ library (no additional dependencies)

Compilation
To compile the code, use g++ (or another C++ compiler):
g++ fp-overflow-checker-mzj21.cpp

Then, output whatever you name the object file, and positive numbers in place of loop_bound
and loop_counter:
./a.out loop_bound loop_counter
