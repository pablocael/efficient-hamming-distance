# -mavx is to support avx instructions
g++ -Wall optimization_challenge.cpp -o optimization_challenge -O3 -std=c++20 -mavx
./optimization_challenge
