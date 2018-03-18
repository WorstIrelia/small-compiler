//
// Created by jason on 3/16/18.
//
#include "semantic.h"
#include "scanner.h"
#include "generate.h"
#include <cstring>
#include <string>
std::unordered_map<int,std::vector<identifier_elem>> symbol_list;
static int cnt=0;
std::unordered_map<std::string,int>map;
int function_cnt=0;
int domain_cnt=0;
char *function_name;
std::vector<std::string> add_del[100][100];
std::unordered_map<std::string,function_elem> function_list;
extern std::unordered_map<int,int>level;
void add(const char *str,int type,int function,int domain){
    std::string key=str;
    if(!map.count(key)){
        map[key]=cnt++;
    }
    symbol_list[map[key]].push_back(identifier_elem(type,function,domain));
}

void delect(const char *str){//碰到}
    std::string key=str;
    symbol_list[map[key]].pop_back();
}


void add_identifer(const char *str,int type,int function_cnt,int domain_cnt){
    if(redefine(str,function_cnt,domain_cnt)) error("redefined");//如果没有重定义
    printf("%s %d %d %d identifier add\n",str,type,function_cnt,domain_cnt);
    add(str,type,function_cnt,domain_cnt);//添加

    mark_add(str,function_cnt,domain_cnt);//生成表达式
}
bool in_symbol_list(const char *str,int function,int domain){
    printf("is_symbol_list %s %d %d\n",str,function,domain);
    std::string key=str;
    if(!map.count(key)) {
        return false;
    }
    std::vector<identifier_elem> &tmp=symbol_list[map[key]];
    //printf("%lu\n",tmp.size());
    if(tmp.size()){
        //printf("%d %d\n",tmp[tmp.size()-1].function,tmp[tmp.size()-1].domain);
        if(tmp[tmp.size()-1].function==function&&tmp[tmp.size()-1].domain<=domain) return true;
        return  false;
    }
    return false;
}
bool redefine(const char *str,int function,int domain){
    std::string key=str;
    if(!map.count(key)) return false;
    std::vector<identifier_elem> &tmp=symbol_list[map[key]];
    if(tmp.size()){
        if(tmp[tmp.size()-1].function==function&&tmp[tmp.size()-1].domain==domain) return true;
        return false;
    }
    return false;
}
bool judge(int ltype,int rtype,const char *str){

    return true;
}

//function
void add_function(const char *str,int type,std::vector<int> &v,bool is_define,bool is_use){
    printf("add function %s %d %d\n",str,is_define,is_use);
    std::string tmp=str;
    function_elem function_tmp;
    for(int i=0;i<v.size();i++){
        function_tmp.argument_list.push_back(v[i]);
    }
    //printf("argument size = %lu\n",function_tmp.argument_list.size());
    function_tmp.type=type;
    function_tmp.isdefine=is_define;
    function_tmp.isuse=is_use;
    function_list[tmp]=function_tmp;
    //printf("argument size = %lu\n",function_list[tmp].argument_list.size());
}
bool function_judge(const char *str,std::vector<int>&v){
    std::string tmp=str;
    std::vector<int>& tmpv=function_list[tmp].argument_list;
    if(function_list[str].isdefine==1) return false;
    //printf("%s %lu %lu\n",str,v.size(),tmpv.size());
    if(v.size()!=tmpv.size()) return false;

    //printf("ok\n");
    for(int i=0;i<v.size();i++){
        if(v[i]!=tmpv[i]) return false;
    }
    return true;
}
bool function_argument_judge(const char *str,std::vector<int>&v){
    std::string tmp=str;
    //printf("judge %s \n",str);
    std::vector<int>& tmpv=function_list[tmp].argument_list;
   // printf("%lu %lu\n",v.size(),tmpv.size());
    if(v.size()!=tmpv.size()) return false;
//    printf("**********\n");
//    for(int i=0;i<v.size();i++){
//        printf("%d %d\n",v[i],tmpv[i]);
//    }
//    printf("**********\n");
    for(int i=0;i<v.size();i++){
        if(v[i]!=tmpv[i]) return false;
    }
    return true;
}
void function_use(const char *str){
    std::string tmp=str;
    function_list[tmp].isuse=1;
}
bool in_function_list(const char *str){
    std::string tmp=str;
    if(function_list.count(tmp)){
        return true;
    }
    return false;
}
int get_function_type(const char *str){
    std::string tmp=str;
    return function_list[tmp].type;
}
//function
int get_identifer_type(const char *str){
    std::string tmp=str;
    std::vector<identifier_elem> &tmpv=symbol_list[map[tmp]];
    return tmpv[tmpv.size()-1].type;
}
void node_init(expr_node* father,expr_node *son){
    father->v.push_back(son);
    son->father=father;
}

bool type_judge(int ltype,int rtype,const char *op){
    if(level[hash(op)]==1&&ltype==NUM) return false;
    if(rtype==NUM||ltype==NUM) return true;
    if(ltype!=rtype) error("type not same");
    return true;
}
