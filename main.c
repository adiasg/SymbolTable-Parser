#include "symbol.h"
#include "symbolList.h"
#include "symbolTable.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>

// <id,type,kind>

void printAvailableInputs() {
    printf("Choose from the following inputs:\n");
    printf("\t");
    printf("symbol\t- Enter <id,type,kind> for a symbol\n");
    printf("\t");
    printf("enter\t- Enter a new scope\n");
    printf("\t");
    printf("exit\t- Exit current scope\n");
}

enum inputType{ENTER, SYMBOL, EXIT};

enum inputType getInputType() {
    static char inputType[7];
    while(1) {
        printf("Enter input: ");
        scanf(" %s", inputType);
        if(!strcmp(inputType, "enter")) {
            printf("You entered: ENTER\n");
            return ENTER;
        }
        else if(!strcmp(inputType, "exit")) {
            printf("You entered: EXIT\n");
            return EXIT;
        }
        else if(!strcmp(inputType, "symbol")) {
            printf("You entered: SYMBOL\n");
            return SYMBOL;
        }
        printf("Invalid input\n");
    }
}

enum type getType() {
    static const char *typeString[] = {"INT", "FLOAT", "DOUBLE", "BOOL"};
    char input[7];
    int i;

    printf("\tEnter type: ");
    scanf(" %s", input);
    //printf("\tYou entered: %s\n", input);
    for(i=0; i<4; i++) {
        if(!strcmp(input, typeString[i])) {
            return (enum type)i;
        }
    }
    while(i==4) {
        //printf("\tYou entered: %s\n", input);
        printf("\tEnter valid type: ");
        scanf(" %s", input);
        for(i=0; i<4; i++) {
            if(!strcmp(input, typeString[i])) {
                return (enum type)i;
            }
        }
    }
    return (enum type)0;
}

enum kind getKind() {
    static const char *kindString[] = {"variable", "function", "parameter"};
    char input[9];
    int i;

    printf("\tEnter kind: ");
    scanf(" %s", input);
    //printf("\tYou entered: %s\n", input);
    for(i=0; i<3; i++) {
        if(!strcmp(input, kindString[i])) {
            return (enum kind)i;
        }
    }
    while(i==3) {
        //printf("\tYou entered: %s\n", input);
        printf("\tEnter valid kind: ");
        scanf(" %s", input);
        for(i=0; i<3; i++) {
            if(!strcmp(input, kindString[i])) {
                return (enum kind)i;
            }
        }
    }
    return (enum kind)0;
}

struct symbol getSymbol() {
    struct symbol *symbol = (struct symbol*)malloc(sizeof(struct symbol));
    char id[7];
    enum type type;
    enum kind kind;

    printf("\tEnter id: ");
    scanf(" %s", id);
    //printf("\tYou entered: %s\n", id);

    type = getType();
    kind = getKind();

    initializeSymbol(symbol, id, type, kind);
    return *symbol;
}

void takeUserInput() {
    struct symbolTable *symbolTable = (struct symbolTable*)malloc(sizeof(struct symbolTable));
    symbolTable->symbolListHead = NULL;
    symbolTable->parentSymbolTable = NULL;
    symbolTable->childSymbolTableListHead = NULL;
    enum inputType input;
    struct symbol *symbol;
    while(symbolTable!=NULL) {
        printAvailableInputs();
        input = getInputType();
        if(input==EXIT) {
            symbolTable = exit_scope(symbolTable);
        }
        else if(input==ENTER) {
            symbolTable = enter_scope(symbolTable);
        }
        else if(input==SYMBOL) {
            symbol = (struct symbol*)malloc(sizeof(struct symbol));
            char id[7];
            enum type type;
            enum kind kind;
            printf("\tEnter id: ");
            scanf(" %s", id);
            type = getType();
            kind = getKind();
            initializeSymbol(symbol, id, type, kind);
            printSymbol(symbol);
            symbolTable_insertSymbol(symbolTable, *symbol);
        }

        if(symbolTable!=NULL) {
            printSymbolList(symbolTable->symbolListHead);
        }
    }
}

int main() {
    //testSymbol();
    //testSymbolList();
    //testSymbolTable();
    takeUserInput();
    return 0;
}
