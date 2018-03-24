#include <bits/stdc++.h>
#include "scanner.h"
#include "parser.h"

FILE *out;

int main() {

    out=fopen("/home/jason/CLionProjects/mybg/out.txt","w");
    freopen("in.txt","r",stdin);

    init();
    gene_start();
    parser();
    generate_all();
    return 0;
}