#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
// <id,type,kind>

enum type{INT, FLOAT, DOUBLE, BOOL};
enum kind{variable, function, parameter};

struct symbol {
    const char *id;
    enum type type;
    enum kind kind;
};

void initializeSymbol(struct symbol *symbol, const char *id, enum type type, enum kind kind);
const char* typeToString(enum type type);
const char* kindToString(enum kind kind);
void printSymbol(struct symbol *symbol);
int symbolcmp(struct symbol symbol1, struct symbol symbol2);
int symbolcmp_id(struct symbol symbol1, struct symbol symbol2);
int symbolCheckId(struct symbol symbol, const char *id);

#endif
