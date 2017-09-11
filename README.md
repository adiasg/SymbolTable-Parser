# Symbol Table and Parser

## Description
This is an implementation of symbol table and parser for an assignment of CSF302 (Principles of Programming Languages) at BITS-Pilani, KK Birla Goa Campus.  

The symbol table has been designed for the semantic analysis stage of the compiler.

## Symbols
+ A symbol is defined to be a set containing `id`, `type`, and `kind`
+ `struct symbol` is defined as
    ```C
    struct symbol {
        const char* id;
        enum type type;
        enum kind kind;
    };
    ```

### Types and constructs
+ Identifier is restricted to `char[32]`
+ Types are restricted to {`INT`, `FLOAT`, `DOUBLE`, `BOOL`}
+ Constructs are restricted to {`variable`, `function`, `parameter`}
+ `enum type` and `enum kind` have been defined in `symbol.h`

### Functions
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
