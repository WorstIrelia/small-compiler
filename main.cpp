#include <bits/stdc++.h>
#include "scanner.h"
#include "parser.h"

FILE *out;

int main() {

    out=fopen("out.txt","w");
    freopen("in.txt","r",stdin);
    freopen("text.txt","w",stdout);
    init();
    gene_start();
    parser();
    gene_prework();
    generate_all();
    return 0;
}