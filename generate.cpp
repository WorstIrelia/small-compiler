//
// Created by jason on 3/17/18.
//

//添加一个全局数据区的数据产生 第一句 bp=sp开始产生
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
#include "semantic.h"
#include "scanner.h"
#include "generate.h"
int tmp_cnt=1;

extern std::vector<std::string> add_del[100][100];
extern std::vector<std::string> add_array_del[100][100];
extern std::unordered_map<int,std::vector<identifier_elem>> symbol_list;
extern std::unordered_map<std::string,function_elem> function_list;
extern std::unordered_map<std::string,std::vector<array_elem>> array_list;
extern std::unordered_map<std::string,int>map;
extern FILE *out;
extern std::unordered_map<long,int>level;
extern int function_cnt;

std::stack<int>function_return_mark;
std::vector<char *>instruction;
std::stack<loop*> loop_stack;
std::stack<_if*> if_stack;
std::vector<char *>pre_work;



int instruction_cnt=0;

static char trans[32];
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
    for(int i=1;i<tmp_cnt;i++) free(it[i]);
    tmp_cnt=1;
}
void gene_two_op(const char *lname,const char *rname,const char *op,const char *tmpname){
    //+= -= *= /= %= ^=qq
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    if(strlen(op)==2){

        if(op[1]=='='&&level[hash(op)]==1){
            sprintf(p,"%c %s %s %s\n",op[0],lname,rname,lname);
        }
        else sprintf(p,"%s %s %s %s\n",op,lname,rname,tmpname);

    }
    else if(strlen(op)==3){
        if(op[2]=='='){
            sprintf(p,"%s %s %s %s\n",op,lname,rname,lname);
        }
        else sprintf(p,"%s %s %s %s\n",op,lname,rname,tmpname);
    }
    else if(op[0]=='='){
        sprintf(p,"%s %s %s\n",op,lname,rname);
    }
    else sprintf(p,"%s %s %s %s\n",op,lname,rname,tmpname);
    if(!function_cnt){
        pre_work.push_back(p);
    }
    else{
        instruction.push_back(p);
        instruction_cnt++;
    }

}

void gene_del(int function,int domain){
    //printf("im in del\n");
    int i=(int)add_del[function][domain].size();
    i--;
    for(;i>=0;i--){
        symbol_list[map[add_del[function][domain][i]]].pop_back();
    }
    add_del[function][domain].clear();
    //printf("del ok1\n");
    i=(int )add_array_del[function][domain].size();
    i--;
    for(;i>=0;i--){
        array_list[add_array_del[function][domain][i]].pop_back();
    }
    add_array_del[function][domain].clear();

}

void mark_add(const char *str,int function,int domain){
    std::string tmp=str;
    add_del[function][domain].push_back(tmp);

}
void mark_array_add(const char *str,int function,int domain){
    add_array_del[function][domain].push_back(str);
}

void gene_add(const char *str){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"add %s\n",str);
    if(!function_cnt){
        pre_work.push_back(p);
    }
    else{
        instruction.push_back(p);
        instruction_cnt++;
    }

    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"push\n");
    if(!function_cnt){
        pre_work.push_back(p);
    }
    else{
        instruction.push_back(p);
        instruction_cnt++;
    }

}
void gene_head_while(const char *str,_while *tmp){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= %%j %s\n",str);
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"jt %d\n",instruction_cnt+2);
    instruction.push_back(p);
    instruction_cnt++;
    p=NULL;
    instruction.push_back(p);
    tmp->_false=instruction_cnt;
    instruction_cnt++;
}
void gene_tail_while(_while *tmp) {
    char *p = (char *) malloc(INSTRUCTION_SIZE);
    sprintf(p, "jump %d\n", tmp->begin);
    instruction.push_back(p);
    instruction_cnt++;

    p = (char *) malloc(INSTRUCTION_SIZE);
    sprintf(p, "jf %d\n", instruction_cnt);
    instruction[tmp->_false] = p;
    for(int i=0;i<tmp->v.size();i++){
        p = (char *) malloc(INSTRUCTION_SIZE);
        sprintf(p, "jump %d\n", instruction_cnt);
        instruction[tmp->v[i]] = p;
    }
    tmp->v.clear();

}
void gene_head_for(const char *str,_for *tmp){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= %%j %s\n",str);
    instruction.push_back(p);
    instruction_cnt++;
    p=NULL;
    instruction.push_back(p);
    tmp->iftrue=instruction_cnt;
    instruction_cnt++;
    instruction.push_back(p);
    tmp->iffalse=instruction_cnt;
    instruction_cnt++;
}
void gene_mid_for(_for *tmp){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"jump %d\n",tmp->begin);
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"jt %d\n",instruction_cnt);
    instruction[tmp->iftrue]=p;

}
void gene_tail_for(_for *tmp){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"jump %d\n",tmp->expr3);
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"jf %d\n",instruction_cnt);
    instruction[tmp->iffalse]=p;
    for(int i=0;i<tmp->v.size();i++){
        p = (char *) malloc(INSTRUCTION_SIZE);
        sprintf(p, "jump %d\n", instruction_cnt);
        instruction[tmp->v[i]] = p;
    }
    tmp->v.clear();
}

void gene_head_if(const char *str,_if *tmp){
    //printf("%s ddddddddddd\n",str);
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= %%j %s\n",str);
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"jt %d\n",instruction_cnt+2);
    instruction.push_back(p);
    instruction_cnt++;
    p=NULL;
    instruction.push_back(p);
    tmp->jf.push_back(instruction_cnt);
    instruction_cnt++;

}
void gene_tail_if(_if* tmp){
    char *p=NULL;
    instruction.push_back(p);
    tmp->jump.push_back(instruction_cnt);
    instruction_cnt++;
}
void gene_end_if(_if *tmp){
    if(tmp->begin.size()==tmp->jf.size()){
        for(int i=1;i<tmp->begin.size();i++){
            char *p=(char *)malloc(INSTRUCTION_SIZE);
            sprintf(p,"jf %d\n",tmp->begin[i]);
            instruction[tmp->jf[i-1]]=p;
        }
        char *p=(char *)malloc(INSTRUCTION_SIZE);
        sprintf(p,"jf %d\n",instruction_cnt);
        instruction[tmp->jf[tmp->jf.size()-1]]=p;
    }
    else{
        for(int i=1;i<tmp->begin.size();i++){
            char *p=(char *)malloc(INSTRUCTION_SIZE);
            sprintf(p,"jf %d\n",tmp->begin[i]);
            instruction[tmp->jf[i-1]]=p;
        }
    }
    for(int i=0;i<tmp->jump.size();i++){
        char *p=(char *)malloc(INSTRUCTION_SIZE);
        sprintf(p,"jump %d\n",instruction_cnt);
        instruction[tmp->jump[i]]=p;
    }
}
void gene_continue(){
    loop *p=loop_stack.top();
    if(p->type==WHILE){
        _while *tmp=(_while*)p;
        char *q = (char *) malloc(INSTRUCTION_SIZE);
        sprintf(q, "jump %d\n", tmp->begin);
        instruction.push_back(q);
        instruction_cnt++;
    }
    else{
        _for *tmp=(_for*)p;
        char *q = (char *) malloc(INSTRUCTION_SIZE);
        sprintf(q, "jump %d\n", tmp->expr3);
        instruction.push_back(q);
        instruction_cnt++;
    }
}
void gene_break(){
    loop *p=loop_stack.top();
    if(p->type==WHILE){
        _while *tmp=(_while*)p;
        char *q = NULL;
        //sprintf(q, "jump %d\n", tmp->begin);
        tmp->v.push_back(instruction_cnt);
        instruction.push_back(q);
        instruction_cnt++;
    }
    else{
        _for *tmp=(_for*)p;
        char *q = NULL;
        //sprintf(q, "jump %d\n", tmp->begin);
        tmp->v.push_back(instruction_cnt);
        instruction.push_back(q);
        instruction_cnt++;
    }

}

void gene_call_begin(){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"- sp bp (sp)\n");
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= bp sp\n");
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"+ sp 16 sp\n");
    instruction.push_back(p);
    instruction_cnt++;
    p=NULL;
    //sprintf(p,"= (sp+8) %d\n");//fanhuidizhi
    instruction.push_back(p);
    function_return_mark.push(instruction_cnt);
    instruction_cnt++;
}
void gene_call_end(const char *str,const char *ret){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"call %s\n",str);
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= (bp+8) %d\n",instruction_cnt);
    instruction[function_return_mark.top()]=p;
    function_return_mark.pop();
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= %s %%a\n",ret);//zm jiexi biaodashi
    instruction.push_back(p);
    instruction_cnt++;
}

void gene_add_array(const char *str,long siz){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"addar %s\n",str);
    if(!function_cnt){
        pre_work.push_back(p);
    }
    else{
        instruction.push_back(p);
        instruction_cnt++;
    }

    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"+ sp %ld sp\n",siz*8);
    if(!function_cnt){
        pre_work.push_back(p);
    }
    else{
        instruction.push_back(p);
        instruction_cnt++;
    }

}
void gene_offset(const char *str,const char *dest){
    std::vector<long>v;
    v.push_back(1);
    long tmp=1;
    std::vector<int>& tmpv=array_list[str].back().dimen;
    int offset=array_list[str].back().dimension;
    int l=(int)tmpv.size()-1;
    for(int i=l;i>=1;i--){
        tmp*=tmpv[i];
        v.push_back(tmp);
    }
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= %%0 0\n");
    instruction.push_back(p);
    instruction_cnt++;
    while(offset){
        p=(char *)malloc(INSTRUCTION_SIZE);
        sprintf(p,"* (sp-%d) %ld (sp-%d) %%0\n",offset*8,v[offset-1],offset*8);
        instruction.push_back(p);
        instruction_cnt++;
        p=(char *)malloc(INSTRUCTION_SIZE);
        sprintf(p,"+ %%0 (sp-%d) %%0\n",offset*8);
        instruction.push_back(p);
        instruction_cnt++;
        offset--;
    }
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= %s %%0\n",dest);
    instruction.push_back(p);
    instruction_cnt++;
    offset=array_list[str].back().dimension;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"- sp %d sp\n",offset*8);
    instruction.push_back(p);
    instruction_cnt++;
}
void gene_set_offset(const char *str){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= (sp) %s\n",str);
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"push\n");
    instruction.push_back(p);
    instruction_cnt++;
}

void generate_all(){
    scan();
    for(int i=0;i<instruction.size();i++){
        fprintf(out,"%d %s",i,instruction[i]);
    }
}

void gene_lea(const char *str,int offset){
    offset+=16;
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"add %s\n",str);
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"push\n");
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= %s (bp+%d)\n",str,offset);
    instruction.push_back(p);
    instruction_cnt++;
}
void gene_real_argument(const char *str){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= (sp) %s\n",str);
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"push\n");
    instruction.push_back(p);
    instruction_cnt++;
}
void gene_return(const char *str){
    char *p;
    if(str) {
        p=(char *)malloc(INSTRUCTION_SIZE);
        sprintf(p,"= %%a %s\n",str);
        instruction.push_back(p);
        instruction_cnt++;
    }
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= sp bp\n");
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"- bp (sp) bp\n");
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"ret (sp+8)\n");
    instruction.push_back(p);
    instruction_cnt++;

}
void gene_start(){
    char *p=(char *)malloc(INSTRUCTION_SIZE);
    memset(p,0,sizeof(p));
    sprintf(p,"\n");
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= bp sp\n");
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"+ sp 16 sp\n");
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"= (bp+8) 0\n");
    instruction.push_back(p);
    instruction_cnt++;
    p=(char *)malloc(INSTRUCTION_SIZE);
    sprintf(p,"call main\n");
    instruction.push_back(p);
    instruction_cnt++;
}
void gene_prework(){
    for(int i=0;i<pre_work.size();i++){
        fprintf(out,"# %s",pre_work[i]);
    }
}
void del(int num){
    for(int i=0;i<num;i++){
        instruction_cnt--;
        free(instruction[instruction_cnt]);
        instruction.pop_back();
    }
}
void scan(){
    for(int i=0;i<instruction_cnt;i++){
        char tmp[128];
        char *p=instruction[i];
        sscanf(p,"%s",tmp);
        if(!strcmp(tmp,"call")){
            p+=5;
            sscanf(p,"%s",tmp);
            int entry=function_list[tmp].entry;
            if(entry==0){
                printf("%s is not defined\n",tmp);
                error("");
            }
            sprintf(instruction[i],"call %d\n",entry);
        }
    }
}
void return_test(){
    char tmp[128];
    sscanf(instruction[instruction_cnt-1],"%s",tmp);
    if(strcmp(tmp,"ret")){
        error("you may forget return..");
    }
}