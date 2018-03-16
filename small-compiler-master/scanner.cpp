//
// Created by jason on 3/14/18.
//
#include <string>
#include <cstdio>
#include <cstring>
#include <unordered_map>
#include "scanner.h"
#include <iostream>
#include "error.h"
#define  MAXSIZE 128
#define  NEXT_CHAR now_char=next_char;next_char=getchar()
static char next_char=' ',now_char=' ';

static std::unordered_map<int,int> f;
int hash(const char *);
std::unordered_map<int,int>level;
char str[MAXSIZE];
int num;

void init(){
    f[hash("int")]=TYPE;
    f[hash("while")]=RESERVER;
    f[hash("for")]=RESERVER;
    f[hash("if")]=RESERVER;
    f[hash("else")]=RESERVER;
    f[hash("return")]=RESERVER;
    f[hash("break")]=RESERVER;
    f[hash("continue")]=RESERVER;
    level[hash("=")]=1;
    level[hash("+=")]=1;
    level[hash("-=")]=1;
    level[hash("*=")]=1;
    level[hash("/=")]=1;
    level[hash("&=")]=1;
    level[hash("^=")]=1;
    level[hash("!=")]=1;
    level[hash("<<=")]=1;//3
    level[hash(">>=")]=1;//3
    level[hash("||")]=2;
    level[hash("&&")]=3;
    level[hash("|")]=4;
    level[hash("^")]=5;
    level[hash("&")]=6;
    level[hash("==")]=7;
    level[hash("!=")]=7;
    level[hash("<")]=8;
    level[hash("<=")]=8;
    level[hash(">=")]=8;
    level[hash(">")]=8;
    level[hash("<<")]=9;
    level[hash(">>")]=9;
    level[hash("+")]=10;
    level[hash("-")]=10;
    level[hash("*")]=11;
    level[hash("/")]=11;
    level[hash("%")]=11;
    //level[hash("[]")]=12;




}
int hash(const char *str){//hash一个字符串
    int res=0;
    int len=strlen(str);
    for(int i=0;i<len;i++){
        res=res*10007+str[i];
    }
    return res;
}
int get_next_token(){//返回下一个词
    NEXT_CHAR;

    while(now_char==' '||now_char=='\n'||now_char=='\n'){
        NEXT_CHAR;
    }
    if(isdigit(now_char)){
        str[0]=0;
        num=now_char-48;
        while(isdigit(next_char)){
            NEXT_CHAR;
            num=num*10+now_char-48;
        }
        std::cout<<num<<std::endl;
        if(isalpha(next_char)){
            error("error in get_next_token");
        }
        return NUM;
    }
    if(isalpha(now_char)){

        char *p=str;
        *p=now_char;
        while(isalnum(next_char)){
            NEXT_CHAR;
            *(++p)=now_char;
        }
        *(++p)=0;
        printf("%s\n",str);
        if(f.count(hash(str))) return f[hash(str)];

        return IDENTIFIER;
    }
    if(now_char==EOF){
        return EOF;
    }
    str[0]=now_char;
    int tmp=str[0]*10007+next_char;
    if(level.count(tmp)){
        str[1]=next_char;
        NEXT_CHAR;


        str[2]=0;
    }
    else str[1]=0;
    printf("%s\n",str);
    switch (str[0]){
        case '{':
            return LBIGBRACKET;
        case '}':
            return RBIGBRACKET;
        case '[':
            return LMIDBRACKET;
        case ']':
            return RMIDBRACKET;
        case '(':
            return LSMLBREAKET;
        case ')':
            return RSMLBREAKET;
        case ',':
            return COMMA;
        case ';':
            return SEMICOLON;
        default:
            return OPERATOR;
    }

}
