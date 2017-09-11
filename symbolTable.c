#include "symbolTable.h"
#include <stdlib.h>

struct symbolTableListEntry* symbolTableListEntry_initializeEntry() {
    struct symbolTableListEntry *symbolTableListEntry = (struct symbolTableListEntry*) malloc(sizeof(struct symbolTableListEntry));
    symbolTableListEntry->entry = (struct symbolTable*) malloc(sizeof(struct symbolTable));
    symbolTableListEntry->nextEntry = NULL;
    return symbolTableListEntry;
}

struct symbolTableListEntry* symbolTableList_insertEntry(struct symbolTableListEntry *head) {
    struct symbolTableListEntry *headTemp = symbolTableListEntry_initializeEntry();
    headTemp->nextEntry = head;
    return headTemp;
}

struct symbolTableListEntry* symbolTableList_deleteEntry(struct symbolTableListEntry *head, struct symbolTable *symbolTable) {
    if(head==NULL) {
        return NULL;
    }
    if(head->entry==symbolTable) {
        return head->nextEntry;
    }
    struct symbolTableListEntry *current = head;
    struct symbolTableListEntry *previous = NULL;
    while(current!=NULL && current->entry!=symbolTable) {
        previous = current;
        current = current->nextEntry;
    }
    if(current!=NULL) {
        previous->nextEntry = current->nextEntry;
        free(current->entry);
        free(current);
    }
    return head;
}

void symbolTableList_freeList(struct symbolTableListEntry *head) {
    if(head==NULL) {
        return;
    }
    struct symbolTableListEntry *next;
    next = head->nextEntry;
    while(head!=NULL) {
        free(head->entry);
        next = head->nextEntry;
        free(head);
        head = next;
    }
}

struct symbolTable* symbolTable_getParent(struct symbolTable* symbolTable) {
        return symbolTable->parentSymbolTable;
}

struct symbolTable* symbolTable_addChild(struct symbolTable* symbolTable) {
    struct symbolTableListEntry *childSymbolTableListEntry;
    childSymbolTableListEntry = symbolTableListEntry_initializeEntry();
    symbolTable->childSymbolTableListHead = symbolTableList_insertEntry(childSymbolTableListEntry);
    struct symbolTable *childSymbolTable = (struct symbolTable*)childSymbolTableListEntry->entry;
    childSymbolTable->parentSymbolTable = symbolTable;
    return childSymbolTable;
}

struct symbolTable* symbolTable_deleteChild(struct symbolTable* symbolTable) {
    //printf("symbolTable_deleteChild()\n");
    struct symbolTable *parentSymbolTable = symbolTable_getParent(symbolTable);
    if(parentSymbolTable!=NULL) {
        symbolTableList_deleteEntry(parentSymbolTable->childSymbolTableListHead, symbolTable);
    }
    //printf("symbolTableList_freeList()\n");
    symbolTableList_freeList(symbolTable->childSymbolTableListHead);
    //printf("symbolList_freeList()\n");
    symbolList_freeList(symbolTable->symbolListHead);
    return parentSymbolTable;
}

struct symbol* symbolTable_getSymbol(struct symbolTable *symbolTable,  const char *id) {
    return symbolList_getSymbol(symbolTable->symbolListHead, id);
}

void symbolTable_insertSymbol(struct symbolTable *symbolTable, struct symbol symbol) {
    symbolTable->symbolListHead = symbolList_insertEntry(symbolTable->symbolListHead, symbol);
}

void symbolTable_deleteSymbol(struct symbolTable *symbolTable, const char *id) {
    symbolTable->symbolListHead = symbolList_deleteEntry(symbolTable->symbolListHead, id);
}

void insert(struct symbolTable *symbolTable, const char *id, enum type type, enum kind kind) {
    struct symbol symbol;
    initializeSymbol(&symbol, id, type, kind);
    symbolTable_insertSymbol(symbolTable, symbol);
}

struct symbol* lookup(struct symbolTable *symbolTable, const char *id) {
    struct symbolTable *symbolTableIter = symbolTable;
    struct symbol *symbol = symbolTable_getSymbol(symbolTableIter, id);
    while(symbol==NULL) {
        symbolTableIter = symbolTable_getParent(symbolTableIter);
        if(symbolTableIter==NULL) {
            break;
        }
        symbol = symbolTable_getSymbol(symbolTableIter, id);
    }
    if(symbol==NULL) {
        printf("******************** ERROR! ********************\n");
        printf("lookup for id: %s returned NULL\n", id);
        printf("************************************************\n");
    }
    return symbol;
}

struct symbolTable* enter_scope(struct symbolTable* symbolTable) {
    return symbolTable_addChild(symbolTable);
}

struct symbolTable* exit_scope(struct symbolTable* symbolTable) {
    return symbolTable_getParent(symbolTable);
}
