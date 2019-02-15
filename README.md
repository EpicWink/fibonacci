# Fibonacci generation
The goal of this project is to precisely generate large fibonacci numbers as fast as possible, within
RAM, CPU and storage limitations. Specifically, we're aiming for a x86 64-bit 8-thread CPU, with 16GB of RAM, and 500GB of storage.

## Pre-requisites
* A C compiler, such as [GCC](https://gcc.gnu.org/)

## Building
Assuming GCC, we need 64-bit compilation
```bash
gcc fibonacci.c -o fib -lm -m64 -O3
```

## Running
```bash
./fib
```
