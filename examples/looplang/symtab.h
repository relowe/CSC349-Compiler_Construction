// Symbol table for looplang
// Based on the symtab for Ledgard by Lee Wittenberg
// Adapted for looplang by Robert Lowe
#ifndef SYMTAB_H
#define SYMTAB_H

#include <string>
#include <set>

struct Symbol_Table {
   std::set<std::string> tab;    // the table itself
   std::set<std::string> undef;  // undefined identifiers
};

extern Symbol_Table symtab;   // global symbol table



#endif
