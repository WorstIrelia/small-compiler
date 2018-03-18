#include <bits/stdc++.h>
#include "scanner.h"
#include "parser.h"
char tmp[100];
FILE *out;

int main() {

    out=fopen("out.txt","w");
    freopen("in.txt","r",stdin);
    init();
    parser();
    //test();
    //printf("success\n");
    return 0;
}