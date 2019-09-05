/**
   @file typecheck.h
   @author Lee Wittenberg
   @date 2017-06-09
   @version 2.0

   Common type-checking functions
 */
#ifndef TYPECHECK_H
#define TYPECHECK_H

#include <iostream>

/**
   Report a type mismatch error.  Must be used for all type error reporting.

   @param line  number of line on which the error occurred
 */
inline void report_type_error(int line)
{
   std::cerr << "Type Mismatch Error on line " << line << std::endl;
}

#endif
