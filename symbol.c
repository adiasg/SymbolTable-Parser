#include "symbol.h"
#include <string.h>

static const char *typeString[] = {"INT", "FLOAT", "DOUBLE", "BOOL"};
static const char *kindString[] = {"variable", "function", "parameter"};

void initializeSymbol(struct symbol *symbol, const char *id, enum type type, enum kind kind) {
    symbol->id = id;
    symbol->type = type;
    symbol->kind = kind;
}

const char* typeToString(enum type type) {
    return typeString[type];
}

const char* kindToString(enum kind kind) {
    return kindString[kind];
}

void printSymbol(struct symbol *symbol) {
    if(symbol==NULL) {
        printf("symbol==NULL\n");
        return;
    }
    printf("<%s,%s,%s>\n", symbol->id, typeToString(symbol->type), kindToString(symbol->kind));
}

int symbolcmp(struct symbol symbol1, struct symbol symbol2) {
    if(
        symbol1.kind==symbol2.kind &&
        symbol1.type==symbol2.type &&
        strcmp(symbol1.id,symbol2.id)==0
    ) {
        return 0;
    }
    return 1;
}

int symbolcmp_id(struct symbol symbol1, struct symbol symbol2) {
    if(strcmp(symbol1.id,symbol2.id)==0) {
        return 0;
    }
    return 1;
}

int symbolCheckId(struct symbol symbol, const char *id) {
    if(strcmp(symbol.id,id)==0) {
        return 0;
    }
    return 1;
}
