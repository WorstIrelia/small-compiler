#include <bits/stdc++.h>
#include "scanner.h"
#include "parser.h"
#include "generate.h"
char tmp[100];
FILE *out;

int main() {

    out=fopen("out.txt","w");
    freopen("in.txt","r",stdin);
    init();
    parser();
    generate_all();
    //test();
    //printf("success\n");
    return 0;
}