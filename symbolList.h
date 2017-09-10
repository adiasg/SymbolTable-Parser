#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

#include "symbol.h"

struct symbolListEntry {
    struct symbol symbol;
    struct symbolListEntry *nextEntry;
};

void printSymbolList(struct symbolListEntry *head);
struct symbolListEntry* symbolList_findEntry(struct symbolListEntry *head,  const char *id);
struct symbol* symbolList_getSymbol(struct symbolListEntry *head,  const char *id);
struct symbolListEntry* symbolList_insertEntry(struct symbolListEntry *head, struct symbol symbol);
struct symbolListEntry* symbolList_deleteEntry(struct symbolListEntry *head, const char *id);

#endif
