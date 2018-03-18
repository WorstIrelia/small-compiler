//
// Created by jason on 3/16/18.
//

#ifndef COMPILER_SEMANTIC_H
#define COMPILER_SEMANTIC_H

#include <vector>
#include <unordered_map>
#include "error.h"
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


//变量名 = 变量名 op 变量名
struct expr_node{



    expr_node *father;
    std::vector<expr_node*>v;

    char *lname;
    char *rname;
    char *retname;
    //测试用

    char op[3];
    int ltype;
    int rtype;
    int rettype;


    expr_node(){
        v.clear();
        father=NULL;
        lname=NULL;
        rname=NULL;
        retname==NULL;
    };
    //virtual


};




//符号表中函数
struct function_elem{
    //char name[128];//报错
    int type;//返回值的类型
    bool isdefine;//是否定义
    bool isuse;//最后扫一遍四元式确定有没有没有使用去没有define的
    std::vector<int>argument_list;

};
//符号表中的标识符
struct identifier_elem {
    //char name[128];//报错
    int type;
    int function;
    int domain;

    identifier_elem(int type, int function, int domain) : type(type), function(function), domain(domain) {};
};



void add_identifer(const char *str,int type,int function,int domain);//封装了增加一个变量 包括出错处理和添加和生成代码
void add(const char *str,int type,int function,int domain);//添加一个元素到符号表
bool in_symbol_list(const char *str,int function,int domain);//在符号表中吗
bool redefine(const char *str,int function,int domain);//判断是否是重复定义
int get_identifer_type(const char *str);//得到符号的属性


void add_function(const char *str,int type,std::vector<int> &v,bool isdefine,bool isuse);////增加一个函数到函数表中
bool function_judge(const char *str,std::vector<int>&v);//声明过 判断是不是这个函数的定义
bool in_function_list(const char *str);//判断这个函数有没有声明过
void function_use(const char *str);//这个函数使用了一次
int get_function_type(const char *str);//得到函数的类型
bool function_argument_judge(const char *str,std::vector<int>&v);//函数调用和函数定义是否匹配

void node_init(expr_node*father,expr_node*son);
bool type_judge(int ltype,int rtype,const char *op);
#endif //COMPILER_SEMANTIC_H
