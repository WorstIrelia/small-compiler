//
// Created by jason on 3/14/18.
//
#include "error.h"
#include <cstdio>
#include <cstdlib>
#include <stdarg.h>
void error(const char *str,...){
    va_list ag;
    va_start(ag,str);
    while(*str){
        while(*str!='%'&&*str){
            fprintf(stderr,"%c",*str);
            str++;
        }
        if(*str==0) break;
        str++;
        switch (*str){
            case 'd':
                fprintf(stderr,"%d",va_arg(ag,int));
                break;
            case 's':
                fprintf(stderr,"%s",va_arg(ag,char *));
                break;
            case 'l':
                str++;
                if(*str=='u'){
                    fprintf(stderr,"%lu",va_arg(ag,unsigned long));
                }
                else if(*str=='d'){
                    fprintf(stderr,"%ld",va_arg(ag,long));
                }
                break;
            case 'u':
                fprintf(stderr,"%u",va_arg(ag,unsigned int));
                break;
        }
        str++;
    }
    va_end(ag);
    exit(-1);

}