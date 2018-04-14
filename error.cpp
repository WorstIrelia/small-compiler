//
// Created by jason on 3/14/18.
//
#include "error.h"
#include <cstdio>
#include <cstdlib>
#include <stdarg.h>
extern int line_num;
void error(const char *str,...){
    va_list ag;
    va_start(ag,str);
    while(*str){
        while(*str!='%'&&*str){
            printf("%c",*str);
            str++;
        }
        if(*str==0) break;
        str++;
        switch (*str){
            case 'd':
                printf("%d",va_arg(ag,int));
                break;
            case 's':
                printf("%s",va_arg(ag,char *));
                break;
            case 'l':
                str++;
                if(*str=='u'){
                    printf("%lu",va_arg(ag,unsigned long));
                }
                else if(*str=='d'){
                    printf("%ld",va_arg(ag,long));
                }
                break;
            case 'u':
                printf("%u",va_arg(ag,unsigned int));
                break;
        }
        str++;
    }
    va_end(ag);
    printf("%d\n",line_num);
    exit(-1);

}