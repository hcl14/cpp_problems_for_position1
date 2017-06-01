# C++ problems asked for a certain C++ position


## Problem 1:

The problem is to count numbers from 1 to N and factorize each one. <br/>
It means that numbers aren't supposed to be big and usage of some advanced prime factorization algorithms like Pollard’s Rho is not beneficial. Trial division is used here.<br/>


## Problem 2:

We need to divide vector of size N into M < N equal parts. Extra elements can be located at the beginning and at the end of segmented area, and the size of these tails should be minimal. The result should be indices of the beginning and the end of each part. <br/>

## Problem 3:
The task is to write getopt function for arguments of types `"--my-option-name my-option-val", "--my-option-name=my-option-val", "--my-boolean-option"`. <br/>
Parameters are strings, doubles, etc. Also parameter can be either required or optional. <br/>
`--help` should print info, optional parameters in `[]` <br/>

## Problem 4:
Here we have single-linked list `1->2->...->N`. We want to reorder it in such way: `1->N->2->N-1->...` <br/>
Example: `1-2-3-4-5-6-7-8  =>  1-8-2-7-3-6-4-5`  <br/>

## Comment:
C++ programs are built with g++, flag `-std=c++11` is required.<br/>
Python programs work under Python 2.7 well.<br/>
