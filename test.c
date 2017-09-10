#include "test.h"

void testSymbol() {
    printf("Test for symbol.h\n");
    struct symbol s1, s2, s3;
    initializeSymbol(&s1, "testVar", INT, variable);
    initializeSymbol(&s2, "testVar2", INT, variable);
    initializeSymbol(&s3, "testVar", INT, variable);
    printf("s1: "); printSymbol(&s1);
    printf("s2: "); printSymbol(&s2);
    printf("s3: "); printSymbol(&s3);
    printf("symbolcmp(s1,s2):%d\n", symbolcmp(s1,s2));
    printf("symbolcmp(s1,s3):%d\n", symbolcmp(s1,s3));

    printf("symbolcmp_id(s1,s2):%d\n", symbolcmp_id(s1,s2));
    printf("symbolcmp_id(s1,s3):%d\n", symbolcmp_id(s1,s3));

    printf("symbolCheckId(s1,\"testVar\"):%d\n", symbolCheckId(s1,"testVar"));
    printf("symbolCheckId(s1,\"testVar2\"):%d\n", symbolCheckId(s1,"testVar2"));
    printf("------------------------------------------\n");
}

void testSymbolList() {
    printf("Test for symbolList.h\n");

    struct symbol symbols[10];
    initializeSymbol(&symbols[0], "id[0]", INT, variable);
    initializeSymbol(&symbols[1], "id[1]", INT, variable);
    initializeSymbol(&symbols[2], "id[2]", INT, variable);
    initializeSymbol(&symbols[3], "id[3]", INT, variable);
    initializeSymbol(&symbols[4], "id[4]", INT, variable);
    initializeSymbol(&symbols[5], "id[5]", INT, variable);
    initializeSymbol(&symbols[6], "id[6]", INT, variable);
    initializeSymbol(&symbols[7], "id[7]", INT, variable);
    initializeSymbol(&symbols[8], "id[8]", INT, variable);
    initializeSymbol(&symbols[9], "id[9]", INT, variable);

    struct symbolListEntry *head = NULL;

    for(int i=0; i<10; i++) {
        head = symbolList_insertEntry(head, symbols[i]);
    }

    printSymbolList(head);
    symbolList_insertEntry(head, symbols[2]);

    printf("\n");
    printSymbol(symbolList_getSymbol(head, "id[0]"));
    printSymbol(symbolList_getSymbol(head, "id[5]"));
    printSymbol(symbolList_getSymbol(head, "id[7]"));
    printf("\n");

    printf("Deleteing id[3]\n");
    head = symbolList_deleteEntry(head, "id[3]");
    printSymbolList(head);

    printf("Deleteing id[0]\n");
    head = symbolList_deleteEntry(head, "id[0]");
    printSymbolList(head);

    printf("Deleteing id[9]\n");
    head = symbolList_deleteEntry(head, "id[9]");
    printSymbolList(head);

    printf("Deleteing id[7]\n");
    head = symbolList_deleteEntry(head, "id[7]");
    printSymbolList(head);

    printf("Get id[7]\n");
    printSymbol(symbolList_getSymbol(head, "id[7]"));

    printf("------------------------------------------\n");
}

void testSymbolTable() {
    printf("Test for symbolTable.h\n");

    struct symbol symbols[10];
    initializeSymbol(&symbols[0], "id[0]", INT, variable);
    initializeSymbol(&symbols[1], "id[1]", INT, variable);
    initializeSymbol(&symbols[2], "id[2]", INT, variable);
    initializeSymbol(&symbols[3], "id[3]", INT, variable);
    initializeSymbol(&symbols[4], "id[4]", INT, variable);
    initializeSymbol(&symbols[5], "id[5]", INT, variable);

    struct symbolTable *symbolTable = (struct symbolTable*)malloc(sizeof(struct symbolTable));
    symbolTable->symbolListHead = NULL;
    symbolTable->parentSymbolTable = NULL;
    symbolTable->childSymbolTableListHead = NULL;

    printf("Parent Symbol Table:\n");
    for(int i=0; i<3; i++) {
        symbolTable_insertSymbol(symbolTable, symbols[i]);
    }
    printSymbolList(symbolTable->symbolListHead);

    printf("Child Symbol Table:\n");
    symbolTable = enter_scope(symbolTable);
    for(int i=3; i<6; i++) {
        symbolTable_insertSymbol(symbolTable, symbols[i]);
    }
    printSymbolList(symbolTable->symbolListHead);

    printf("lookup id: id[1] in child\n");
    printSymbol(lookup(symbolTable, "id[1]"));

    symbolTable = exit_scope(symbolTable);
    printf("Parent Symbol Table:\n");
    printSymbolList(symbolTable->symbolListHead);

    printf("lookup id: id[1] in parent\n");
    printSymbol(lookup(symbolTable, "id[1]"));
    printf("lookup id: id[45] in parent\n");
    printSymbol(lookup(symbolTable, "id[45]"));

    printf("------------------------------------------\n");
}
