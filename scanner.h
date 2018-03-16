//
// Created by jason on 3/14/18.
//

#ifndef COMPILER_SCANNER_H
#define COMPILER_SCANNER_H

#define TYPE 0
#define IDENTIFIER 1
#define NUM 2
#define OPERATOR 3
#define SYMBOL 4
#define RESERVER 5
#define LBIGBRACKET 6
#define RBIGBRACKET 7
#define LMIDBRACKET 8
#define RMIDBRACKET 9
#define LSMLBREAKET 10
#define RSMLBREAKET 11
#define COMMA 12
#define SEMICOLON 13
int get_next_token();
int hash(const char *);
void init();
#endif //COMPILER_SCANNER_H
