//
// Created by jason on 3/17/18.
//

#ifndef COMPILER_GENERATE_H
#define COMPILER_GENERATE_H

#include <cstdio>


char *atoi();
char *next_tmp() ;
void delete_tmp();
void gene_two_op(const char *lname,const char *rname,const char *op,const char *tmpname);
void gene_function(const char *function_name,const char *tmpname);
void gene_del(int function,int domian);
void mark_add(const char *str,int function,int domain);
#endif //COMPILER_GENERATE_H
