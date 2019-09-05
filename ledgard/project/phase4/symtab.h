/**
   @file symtab.h
   @author Lee Wittenberg
   @date 2017-06-04
   @version 1.0

   Declarations needed for global symbol table.
 */
#ifndef SYMTAB_H
#define SYMTAB_H

#include <string>
#include <set>
#include <map>
#include "parse-tree.h"

struct Symbol_Table {
   std::map<std::string, Type_Node*> tab;    // the table itself
   std::set<std::string> undef;              // undefined identifiers
   std::set<std::string> dupls;              // multiply-defined identifiers
};

extern Symbol_Table symtab;   // global symbol table

#endif
