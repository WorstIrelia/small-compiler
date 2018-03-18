//
// Created by jason on 3/17/18.
//
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include "semantic.h"
#include "scanner.h"
int tmp_cnt=1;

extern std::vector<std::string> add_del[100][100];
extern std::unordered_map<int,std::vector<identifier_elem>> symbol_list;
extern std::unordered_map<std::string,int>map;
extern FILE *out;
extern std::unordered_map<int,int>level;
char trans[32];
char *it[128];
char *atoi(){
    int cnt=0;
    int tmp=tmp_cnt;
    while(tmp){
        trans[cnt++]=tmp%10+48;
        tmp/=10;
    }
    std::reverse(trans,trans+cnt);
    return trans;
}
char *next_tmp(){
    char *tmp=(char *)malloc(32);
    tmp[0]='%';
    strcpy(tmp+1,atoi());
    it[tmp_cnt++]=tmp;
    return tmp;

}
void delete_tmp(){
    printf("im in delete\n");
    for(int i=1;i<tmp_cnt;i++) free(it[i]);
    tmp_cnt=1;
}
void gene_two_op(const char *lname,const char *rname,const char *op,const char *tmpname){
    //+= -= *= /= %= ^=qq
    if(strlen(op)==2){
        if(op[1]=='='&&level[hash(op)]==1){
            fprintf(out,"%c %s %s %s\n",op[0],lname,rname,lname);
        }
        else fprintf(out,"%s %s %s %s\n",op,lname,rname,tmpname);
    }
    else if(strlen(op)==3){
        if(op[2]=='='){
            fprintf(out,"%s %s %s %s\n",op,lname,rname,lname);
        }
        else fprintf(out,"%s %s %s %s\n",op,lname,rname,tmpname);
    }
    else if(op[0]=='='){
        fprintf(out,"%s %s %s\n",op,lname,rname);
    }
    else fprintf(out,"%s %s %s %s\n",op,lname,rname,tmpname);
}
void gene_function(const char *function_name,const char *tmpname){
    fprintf(out,"call %s\n",function_name);
    fprintf(out,"= %%a %s\n",tmpname);
}

void gene_del(int function,int domain){
    int i=(int)add_del[function][domain].size();
    i--;
    for(;i>=0;i--){
        symbol_list[map[add_del[function][domain][i]]].pop_back();
        //std::cout<<"del"<<' '<<add_del[function][domain][i]<<' '<<function<<' '<<domain<<std::endl;
    }
    add_del[function][domain].clear();

}

void mark_add(const char *str,int function,int domain){
    //fprintf(out,"add %s\n",str);
    std::string tmp=str;
    add_del[function][domain].push_back(tmp);

}