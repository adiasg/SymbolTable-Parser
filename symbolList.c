#include "symbolList.h"
#include <stdlib.h>
#include <string.h>

void printSymbolList(struct symbolListEntry *head) {
    printf("SymbolList:\n");
    while(head!=NULL) {
        printf("\t");
        printSymbol(&(head->symbol));
        head = head->nextEntry;
    }
    //printf("\n");
}

void symbolList_freeList(struct symbolListEntry *head) {
    if(head==NULL) {
        return;
    }
    struct symbolListEntry *next;
    next = head->nextEntry;
    while(head!=NULL) {
        //free(&(head->symbol));
        next = head->nextEntry;
        free(head);
        head = next;
    }
}

static struct symbolListEntry* initializeEntry(struct symbol symbol) {
    struct symbolListEntry *entry = (struct symbolListEntry*) malloc(sizeof(struct symbolListEntry));
    entry->symbol = symbol;
    entry->nextEntry = NULL;
    return entry;
}

struct symbolListEntry* symbolList_findEntry(struct symbolListEntry *head, const char *id) {
    while(head!=NULL && symbolCheckId(head->symbol, id)) {
        head = head->nextEntry;
    }
    return head;
}

struct symbol* symbolList_getSymbol(struct symbolListEntry *head,  const char *id) {
    struct symbolListEntry *entry = symbolList_findEntry(head, id);
    if(entry==NULL) {
        return NULL;
    }
    return &(entry->symbol);
}

struct symbolListEntry* symbolList_insertEntry(struct symbolListEntry *head, struct symbol symbol) {
    //printf("symbolList_insertEntry() for symbol: "); printSymbol(&symbol);
    if(symbolList_findEntry(head, symbol.id)!=NULL) {
        printf("******************** ERROR! ********************\n");
        printf("symbolListEntry with id: %s already present\n", symbol.id);
        printf("************************************************\n");
        return head;
    }
    //printf("Entry not found in list\n");
    if(head==NULL) {
        head = initializeEntry(symbol);
    }
    else {
        struct symbolListEntry *headTemp = head;
        while(headTemp->nextEntry!=NULL) {
            headTemp = headTemp->nextEntry;
        }
        headTemp->nextEntry = initializeEntry(symbol);
    }
    return head;
}

struct symbolListEntry* symbolList_deleteEntry(struct symbolListEntry *head, const char *id) {
    if(head==NULL) {
        return NULL;
    }
    if(!symbolCheckId(head->symbol, id)) {
        return head->nextEntry;
    }
    struct symbolListEntry *current = head;
    struct symbolListEntry *previous = NULL;
    while(current!=NULL && symbolCheckId(current->symbol, id)) {
        previous = current;
        current = current->nextEntry;
    }
    if(current!=NULL) {
        previous->nextEntry = current->nextEntry;
        free(current);
    }
    return head;
}
