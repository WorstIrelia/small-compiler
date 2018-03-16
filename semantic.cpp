//
// Created by jason on 3/16/18.
//
#include "semantic.h"
#include <string>
std::unordered_map<int,std::vector<identifier_elem>> syboml_list;
static int cnt=0;
static std::unordered_map<std::string,int>map;
int function_cnt=0;
int domain_cnt=0;
void add(const char *str,int type,int function,int domain){
    std::string key=str;
    if(!map.count(key)){
        map[key]=cnt++;
    }
    syboml_list[map[key]].push_back(identifier_elem(type,function,domain));
}
void delect(const char *str){//碰到}
    std::string key=str;
    syboml_list[map[key]].pop_back();
}
bool in_symbol_list(const char *str,int function,int domain){
    std::string key=str;
    std::vector<identifier_elem> &tmp=syboml_list[map[key]];
    if(tmp.size()){
        if(tmp[tmp.size()-1].function==function&&tmp[tmp.size()-1].domain<=domain) return true;
        return  false;
    }
    else return false;
}
bool judge(int ltype,int rtype,const char *str){

    return true;
}


void add_function(const char *str,int type,std::vector &v){

}

void node_init(expr_node* father,expr_node *son){
    father->v.push_back(son);
    son->father=father;
}