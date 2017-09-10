#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "symbolList.h"

struct symbolTableListEntry {
    void *entry;
    struct symbolTableListEntry *nextEntry;
};

struct symbolTable {
    struct symbolListEntry *symbolListHead;
    struct symbolTable *parentSymbolTable;
    struct symbolTableListEntry *childSymbolTableListHead;
};

struct symbolTableListEntry* symbolTableListEntry_initializeEntry();
struct symbolTableListEntry* symbolTableList_insertEntry(struct symbolTableListEntry *head);
struct symbolTableListEntry* symbolTableList_deleteEntry(struct symbolTableListEntry *head, struct symbolTable *symbolTable);
void symbolTableList_freeList(struct symbolTableListEntry *head);

struct symbolTable* symbolTable_getParent(struct symbolTable* symbolTable);
struct symbolTable* symbolTable_addChild(struct symbolTable* symbolTable);
struct symbolTable* symbolTable_deleteChild(struct symbolTable* symbolTable);

struct symbol* symbolTable_getSymbol(struct symbolTable *symbolTable,  const char *id);
void symbolTable_insertSymbol(struct symbolTable *symbolTable, struct symbol symbol);
void symbolTable_deleteSymbol(struct symbolTable *symbolTable, const char *id);

void insert(struct symbolTable *symbolTable, const char *id, enum type type, enum kind kind);
struct symbol* lookup(struct symbolTable *symbolTable, const char *id);

struct symbolTable* enter_scope(struct symbolTable* symbolTable);
struct symbolTable* exit_scope(struct symbolTable* symbolTable);

#endif
