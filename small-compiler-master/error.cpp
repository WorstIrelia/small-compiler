//
// Created by jason on 3/14/18.
//
#include "error.h"
#include <cstdio>
#include <cstdlib>
void error(const char *p){
    fprintf(stderr,"%s\n",p);
    exit(-1);
}