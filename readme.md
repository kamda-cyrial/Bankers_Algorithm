# Banker's Algorithm Implementation in C++

This program is a C++ implementation of the Banker's Algorithm, which is used for deadlock avoidance in operating systems. It reads a system snapshot from a file and determines whether the system is in a safe state. If it is, it will also provide a safe sequence of processes.

## Getting Started

These instructions will guide you on how to compile and run the program on your local machine for development and testing purposes.

### Prerequisites

- A Unix/Linux environment
- g++ compiler
- Input data file (formatted as described below)

### Compiling the Program

To compile the program, navigate to the directory containing `bankers_algorithm.cpp` and run the following command:

```sh
g++ -o bankers_algorithm bankers_algorithm.cpp
```

### Running the Program
To run the program, edit input.txt to contain processes and use the following command:
```sh
./bankers_algorithm
```

## Input File Format
The input file should be structured with each process's Allocation and Max resources separated by spaces. The last line represents the Available resources. 
For example:
```sh
0 1 0 7 5 3
2 0 0 3 2 2
3 0 2 9 0 2
2 1 1 2 2 2
0 0 2 4 3 3
3 3 2
```
Each line corresponds to a process's data, where the first three numbers are the allocated resources (A, B, C), and the next three numbers are the maximum demand of resources (A, B, C). The last line indicates the total available resources for A, B, and C.

## Example
Given the above input file, the output should be:
```sh
System is in a safe state.
Safe sequence is: P1 P3 P4 P0 P2
```
This sequence is one of the possible safe sequences for the provided system snapshot where the system is in a safe state.
