//
// Created by jason on 3/16/18.
//

#ifndef COMPILER_SEMANTIC_H
#define COMPILER_SEMANTIC_H

#include <vector>
#include <unordered_map>
//每个递归函数一个节点

//二元表达式符号计算过程中,符号直接分配到当前节点 不往下分 这样保证了是一颗二叉树
//分配符号的有左操作数和右操作数 TYPE 代表identifier
//左操作数从父亲那里获取 右操作数从儿子那里获取
//有符号的分配 LTYPE RTYPE op RETYPE ISTMP 没符号的 TYPE ISTMP传递
//赋值语句不能复制给*strtmp //
//每次进入表达式解析的时候建一次树
//遇到for while if domain+1
//每解析一个函数 function+1
//碰到表达式是一个函数 查在不在函数表 在的话查参数是否匹配 返回type

//先写表达式解析
struct expr_node{



    expr_node *father;
    std::vector<expr_node*>v;

    char lname[128];
    char rname[128];
    char retname[128];
    //测试用
    char name[128];

    char op[3];
    int ltype;
    int rtype
    int rettype;
    bool istmp;


    expr_node(){
        v.clear();
        father=NULL;
    };
    //virtual


};





struct function_elem{
    char name[128];//报错
    int type;
    bool isdefine;
    bool isuse;
    std::vector<int>argument_list;

};

struct identifier_elem{
    char name[128];//报错
    int type;
    int function;
    int domain;

    identifier_elem (int type,int function,int domain):type(type),function(function),domain(domain){};//statement 使用


};
void delect(const char *str);
void add(const char *str,int type,int function,int domain);//添加一个元素到符号表
bool in_symbol_list(const char *str,int function,int domain);
bool judge(int ltype,int rtype,char *str);

void add_function(const char *str,int type,std::vector &v,bool isdefine,bool isuse);
void node_init(expr_node*father,expr_node*son);


#endif //COMPILER_SEMANTIC_H
