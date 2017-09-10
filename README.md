# <center>Symbol Table and Parser</center>

## Description
This is an implementation of symbol table and parser for an assignment of CSF302 (Principles of Programming Languages) at BITS-Pilani, KK Birla Goa Campus.  

The symbol table has been designed for the semantic analysis stage of the compiler.

## Types and constructs
+ Types are restricted to {`INT`, `FLOAT`, `DOUBLE`, `BOOL`}
+ Constructs are restricted to {`variable`, `function`, `parameter`}
+ `enum type` and `enum kind` has been defined in `symbol.h`

## Functions
+ Functions are assumed to have up to two parameters

## Instructions
+ To build:  
    Set `CC` to your choice of C compiler in `Makefile`. Then execute:
    ```bash
    make main.out
    ```
+ To run:
    ```bash
    ./main.out
    ```
