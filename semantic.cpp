//
// Created by jason on 3/16/18.
//
#include "semantic.h"
#include "scanner.h"
#include "generate.h"
#include <cstring>
std::unordered_map<int,std::vector<identifier_elem>> symbol_list;
static int cnt=0;
std::unordered_map<std::string,int>map;
int function_cnt=0;
int domain_cnt=0;
char *function_name;
std::vector<std::string> add_del[100][100];
std::vector<std::string> add_array_del[100][100];
std::unordered_map<std::string,function_elem> function_list;
std::unordered_map<std::string,std::vector<array_elem>> array_list;
extern std::unordered_map<long,int>level;
void add(const char *str,int type,int function,int domain){
    std::string key=str;
    if(!map.count(key)){
        map[key]=cnt++;
    }
    symbol_list[map[key]].push_back(identifier_elem(type,function,domain));
}

bool is_use(const char *str){
    return function_list[str].isuse;
}


void add_identifer(const char *str,int type,int function_cnt,int domain_cnt){
    printf("%s %d %d \n",str,function_cnt,domain_cnt);
    if(redefine(str,function_cnt,domain_cnt)) error("redefined");//如果没有重定义
    //printf("%s %d %d %d identifier add\n",str,type,function_cnt,domain_cnt);
    add(str,type,function_cnt,domain_cnt);//添加

    mark_add(str,function_cnt,domain_cnt);//生成表达式
}
bool in_symbol_list(const char *str,int function,int domain){
    //printf("is_symbol_list %s %d %d\n",str,function,domain);
    std::string key=str;
    if(!map.count(key)) {
        return false;
    }
    std::vector<identifier_elem> &tmp=symbol_list[map[key]];
    if(tmp.size()){
        if(tmp[tmp.size()-1].function==function&&tmp[tmp.size()-1].domain<=domain||tmp[tmp.size()-1].function==0) return true;
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

//function
void add_function(const char *str,int type,std::vector<int> &v,bool is_define,bool is_use,int entry){
    //printf("add function %s %d %d\n",str,is_define,is_use);
    std::string tmp=str;
    function_elem function_tmp;
    for(int i=0;i<v.size();i++){
        function_tmp.argument_list.push_back(v[i]);
    }
    function_tmp.type=type;
    function_tmp.isdefine=is_define;
    function_tmp.isuse=is_use;
    function_tmp.entry=entry;
    function_list[tmp]=function_tmp;
}
bool function_judge(const char *str,std::vector<int>&v){
    std::string tmp=str;
    std::vector<int>& tmpv=function_list[tmp].argument_list;
    if(function_list[str].isdefine==1) return false;
    if(v.size()!=tmpv.size()) return false;

    for(int i=0;i<v.size();i++){
        if(v[i]!=tmpv[i]) return false;
    }
    return true;
}
bool function_argument_judge(const char *str,std::vector<int>&v){
    std::string tmp=str;
    std::vector<int>& tmpv=function_list[tmp].argument_list;
    if(v.size()!=tmpv.size()) return false;
    for(int i=0;i<v.size();i++){
        if(v[i]!=tmpv[i]&&v[i]!=NUM) return false;
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

bool in_array_list(const char *str,int function_cnt,int domain_cnt){
    if(!array_list.count(str)) return false;
    array_elem &tmp=array_list[str].back();
    //printf("array_size %d\n",array_list[str].size());
    if(function_cnt==tmp.function&&domain_cnt==tmp.domain) return true;
    return false;

}
bool is_in_array_list(const char *str,int function_cnt,int domain_cnt){
    if(!array_list.count(str)) return false;
    array_elem &tmp=array_list[str].back();
    //printf("array_size %d\n",array_list[str].size());
    if(function_cnt==tmp.function&&domain_cnt>=tmp.domain||tmp.function==0) return true;
    return false;
}
int get_array_dimen(const char *str){
    //printf("im ss %s\n",str);
    //printf("array_size %d\n",array_list[str].size());
    int tmp=array_list[str].back().dimension;
    //printf("im hhhh\n");
    return array_list[str].back().dimension;
}
void add_array(const char *str,int type,int function_cnt,int domain_cnt,int dimension,std::vector<int>&n){
    array_elem tmp=array_elem(type,function_cnt,domain_cnt,dimension,n);
    array_list[str].push_back(tmp);
    //printf("dddddddddd %s\n",str);
    //printf("sdf %d\n",array_list[str].size());
    mark_array_add(str,function_cnt,domain_cnt);
}
int get_array_type(const char *str){
    return array_list[str].back().type;
}