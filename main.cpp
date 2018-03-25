#include <bits/stdc++.h>
#include "scanner.h"
#include "parser.h"

FILE *out;

int main() {

    out=fopen("/home/jason/Program/mybg/out.txt","w");
    freopen("in.txt","r",stdin);

    init();
    gene_start();
    parser();
    gene_prework();
    generate_all();
    return 0;
}