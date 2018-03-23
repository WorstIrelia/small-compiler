//
// Created by jason on 3/14/18.
//
#include "parser.h"
#include "scanner.h"
#include "semantic.h"
#include "generate.h"
#include <cstring>
#include <stack>


static int mark;
extern int instruction_cnt;
extern int num;
extern char str[];
extern int domain_cnt;
extern int function_cnt;
extern std::unordered_map<int,int> level;
extern std::stack<loop *>loop_stack;
extern std::stack<_if *>if_stack;
static int isloop=0;
expr_node *root=new expr_node();
expr_node *current=root;

static char *func_name;

expr_node* expr(){//奇怪

    auto tmp=new expr_node;

    node_init(current,tmp);
    current=tmp;

    _A();
    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;
    //printf("%s\n",tmp->retname);
    current=tmp->father;

    return current;
}

void _A(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _B();

    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;
    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _A_();
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _A_(){
    if(level[hash(str)]==1){

        current->lname=current->father->retname;
        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _B();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _A_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;

    }
}
void _B(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _C();

    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _B_();
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _B_(){
    //printf("im in _B_\n");
    if(level[hash(str)]==2){


        current->lname=current->father->retname;
        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _C();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _B_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;
    }
}
void _C(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _D();

    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _C_();
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _C_(){
    if(level[hash(str)]==3){


        current->lname=current->father->retname;
        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _D();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _C_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;
    }
}
void _D(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _E();

    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _D_();
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _D_(){
    if(level[hash(str)]==4){


        current->lname=current->father->retname;
        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _E();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _D_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;
    }
}
void _E(){

    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _F();

    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _E_();
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _E_(){
    if(level[hash(str)]==5){


        current->lname=current->father->retname;
        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _F();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _E_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;
    }
}
void _F(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _G();

    tmp->father->retname=tmp->retname;
    //printf("%s test return name\n",tmp->retname);
    tmp->father->rettype=tmp->rettype;

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _F_();
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        //printf("%s test return name\n",tmp->retname);
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _F_(){
    if(level[hash(str)]==6){


        current->lname=current->father->retname;
        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _G();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _F_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;
    }
}
void _G(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _H();

    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;
    //printf("%s test return name\n",tmp->retname);
    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;
    _G_();
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        //printf("%s test return name\n",tmp->retname);
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _G_(){
    if(level[hash(str)]==7){


        current->lname=current->father->retname;

        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _H();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _G_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;
    }
}
void _H(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _I();

    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;
    //printf("%s test return name\n",tmp->retname);
    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _H_();
    //printf("im in\n");
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        //printf("%s test return name fffffffffff\n",tmp->retname);
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _H_(){
    if(level[hash(str)]==8){


        current->lname=current->father->retname;

        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _I();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();
        //printf("okok\n");
        //printf("%s test return name\n",tmp1->father->retname);
        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _H_();
        //printf("%s test return namehhhhhh\n",tmp1->father->retname);
        //printf("%p dddddddddd\n",tmp1->retname);
        if(tmp1->retname) {
            tmp1->father->retname=tmp1->retname;
           // printf("%s test return name\n",tmp1->father->retname);
        }
        //printf("im out\n");
        current=tmp1->father;
    }
}
void _I(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _J();

    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _I_();
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _I_(){
    if(level[hash(str)]==9){


        current->lname=current->father->retname;

        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _J();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _I_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;
    }
}
void _J(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _K();

    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _J_();
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _J_(){
    if(level[hash(str)]==10){


        current->lname=current->father->retname;

        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _K();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;
        _J_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;
    }
}
void _K(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _L();

    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _K_();
    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
}
void _K_(){
    //printf("im in _k_\n");
    if(level[hash(str)]==11){


        current->lname=current->father->retname;

        current->ltype=current->father->rettype;
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _L();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _K_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;
    }
}
void _L(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _M();


    //printf("test %s\n",tmp->retname);
    tmp->father->retname=tmp->retname;
    tmp->father->rettype=tmp->rettype;
    //printf("father test %s\n",tmp->father->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;
    //printf("im in\n");
    _L_();


    if(tmp->retname) {
        tmp->father->retname=tmp->retname;
        tmp->father->rettype=tmp->rettype;
    }
    current=tmp->father;
    //printf("father test2 %s\n",tmp->father->retname);
}
void _L_(){
    //printf("im in _L_\n");
    if(level[hash(str)]==12){
        current->lname=current->father->retname;
        current->ltype=current->father->rettype;
        strcpy(current->op,str);

        NEXT;

        auto *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _M();

        tmp1->father->rname=tmp1->retname;
        tmp1->father->retname=next_tmp();

        tmp1->father->rtype=tmp1->rettype;
        tmp1->father->rettype=tmp1->father->ltype;

        current=tmp1->father;
        if(type_judge(current->ltype,current->rtype,current->op)) gene_two_op(current->lname,current->rname,current->op,current->retname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _L_();

        if(tmp1->retname) tmp1->father->retname=tmp1->retname;
        current=tmp1->father;


    }
}

void _M(){//分析是函数还是变量
    if(!strcmp(str,"(")){
        NEXT;

        expr_node *tmp=new expr_node;
        node_init(current,tmp);
        current=tmp;

        _A();

        tmp->father->retname=tmp->retname;
        tmp->father->rettype=tmp->rettype;
        current=tmp->father;
        if(!strcmp(str,")")){
            NEXT;
        }
        else error("in M");
    }
    else if(mark==NUM){

        current->rettype=NUM;
        current->retname=(char *)malloc(128);
        strcpy(current->retname,str);//换成数字的string

        NEXT;
    }
    else {
        current->retname=(char *)malloc(128);
        strcpy(current->retname,str);
        iden_or_func();
    }
}









void parser(){
    NEXT;
    S();
    printf("success\n");
}
void S(){
    if(mark==TYPE){
        function();
        C();
    }
    else{
        error("error in S()\n");
    }
}
void C(){
    //printf("CCCC\n");
    if(mark==EOF){
        return;
    }
    else if(mark==TYPE){
        S();
    }
    else error("in C,expect type\n");
}

void _argument_list(std::vector<int> &argument_list_v){
    if(mark==COMMA){
        NEXT;
        if(mark==TYPE){
            int tmptype=gettype(str);
            argument_list_v.push_back(tmptype);
            NEXT;
            if(mark==IDENTIFIER){
                add_identifer(str,tmptype,function_cnt,domain_cnt);
                gene_lea(str,(argument_list_v.size()-1)*8);
                NEXT;
                _argument_list(argument_list_v);
            }
            else error("in _arguement_list\n");
        }

    }
    else if(mark==RSMLBREAKET) return ;
    else error("in _arguement_list\n");
}
void argument_list(std::vector<int> &argument_list_v){
    if(mark==TYPE){
        int tmptype=gettype(str);
        argument_list_v.push_back(gettype(str));
        //printf("size %lu\n",argument_list_v.size());
        NEXT;
        if(mark==IDENTIFIER){
            add_identifer(str,tmptype,function_cnt,domain_cnt);
            gene_lea(str,0);
            NEXT;
            if(mark==COMMA) {
                _argument_list(argument_list_v);
            }
            else if(mark==RSMLBREAKET) return;
            else error("in arguement_list,expect ,\n");
        }
        else error("in arguement_list,expect identifier\n");
    }
    else if(mark==RSMLBREAKET) return;
    else error("in arguement_list,expect type or )\n");
}
void function(){
    int type;
    char name[128];
    func_name=name;
    int entry=instruction_cnt;
    if(mark==TYPE){
        type=gettype(str);
        NEXT;
        if(mark==IDENTIFIER) {
            strcpy(name,str);
            NEXT;
            if (mark == LSMLBREAKET) {
                NEXT;
                function_cnt++;
                domain_cnt=0;
                std::vector<int>argument_list_v;
                argument_list_v.clear();
                argument_list(argument_list_v);//得到参数信息
                if (mark == RSMLBREAKET) {
                    NEXT;
                    if (mark == LBIGBRACKET) {//定义函数
                        if(in_function_list(name)){//如果声明过 要求参数相等 而且没定义
                            if(!function_judge(name,argument_list_v)) {

                                error("error in funciont %s\n",name);
                            }
                        }
                        add_function(name,type,argument_list_v,1,is_use(name),entry);//增加函数表 接下来就是要生成代码 所以对函数体和域进行操作
                        NEXT;
                        code_block();
                        //return_test();//有问题

                        if (mark == RBIGBRACKET) {
                            gene_del(function_cnt,domain_cnt);//在变量表里删除这个域内的所以变量
                            NEXT;
                            return;
                        }
                        else error("in function,expect }\n");
                    }
                    else if(mark==SEMICOLON){//这只是个函数声明
                        if(in_function_list(name)){
                            //printf("function %s ",name);
                            error("fucntion is redefine %s\n",name);
                        }
                        del(argument_list_v.size()*3);
                        add_function(name,type,argument_list_v,0,0,0);
                        NEXT;
                    }
                    else error("in function,expect {\n");
                }
                else error("in function,expect )\n");
            }
            else error("in function,expect (\n");
        }
        else error("in function,expect identifier\n");
    }
    else error("in function,expect type\n");
}


void sentence(){
    if(mark==TYPE){
        statement();
    }
    else if(mark==IDENTIFIER||mark==LSMLBREAKET){
        //printf("im in aaaaaaaaaa\n");
        expr();
        delete_tmp();
    }
}
void equal(int type,const char *tmpstr){
    //printf("im in\n");
    if(!strcmp(str,"=")){
        NEXT;
        auto p=expr();
        type_judge(type,p->rettype,"=");
        gene_two_op(tmpstr,p->retname,"=",NULL);
        delete_tmp();
    }
}//judge
void X(int type){
    if(mark==COMMA){
        NEXT;
        if(mark==IDENTIFIER){
            char tmpstr[128];
            strcpy(tmpstr,str);
            add_identifer(str,type,function_cnt,domain_cnt);
            gene_add(str);
            NEXT;
            equal(type,tmpstr);//类型匹配
            X(type);
        }
        else error("in X,expect identifier\n");
    }
    else if(mark==SEMICOLON) return;
    else error("in X,expect , or ;\n");
}

void statement(){
    int type;
    if(mark==TYPE){
        type=gettype(str);//获取变量类型
        NEXT;
        if(mark==IDENTIFIER){
            char tmpstr[128];
            strcpy(tmpstr,str);
            add_identifer(str,type,function_cnt,domain_cnt);
            gene_add(str);
            NEXT;
            equal(type,tmpstr);//类型匹配
            X(type);
        }
        else error("in statement,expect identifier\n");
    }
    else error("in statement,expect type\n");
    delete_tmp();
}




void _real_argument_list(std::vector<int> &real_argument_list_v){
    if(mark==COMMA){
        NEXT;
        auto p=expr();
        real_argument_list_v.push_back(p->rettype);
        gene_real_argument(p->retname);
        _real_argument_list(real_argument_list_v);
    }
    else if(mark==RSMLBREAKET) {
        return ;
    }
    else error("in _real_argument_list");
}
void real_argument_list(std::vector<int> &real_argument_list_v){
    if(mark==RSMLBREAKET) return;
    auto p=expr();
    real_argument_list_v.push_back(p->rettype);
    gene_real_argument(p->retname);
    _real_argument_list(real_argument_list_v);
}
void func(const char *function_name){
    if(mark==LSMLBREAKET){
        NEXT;
        std::vector<int> real_argument_list_v;
        real_argument_list_v.clear();
        real_argument_list(real_argument_list_v);//得到实参表
        if(mark==RSMLBREAKET){
            if(function_argument_judge(function_name,real_argument_list_v)){
                function_use(function_name);
            }
            else error("arguments don't match");
            NEXT;
            return;
        }
        else error("in func");
    }
    else error("in func");
}

void iden_or_func(){
    if(mark==IDENTIFIER){
        NEXT;
        if(mark==LSMLBREAKET){
            if(!in_function_list(current->retname)) {
                printf("%s ",current->retname);
                error("not statement");
            }
            char *function_name=(char *)malloc(128);
            strcpy(function_name,current->retname);
            gene_call_begin();
            func(function_name);

            current->rettype=get_function_type(function_name);//函数的返回值类型 修改
            char *p=next_tmp();
            gene_call_end(function_name,p);

            //gene_function(function_name,p);
            current->retname=p;
            free(function_name);
            return ;
        }
        else if(mark==OPERATOR||mark==RSMLBREAKET||mark==SEMICOLON||mark==COMMA) {

            if(!in_symbol_list(current->retname,function_cnt,domain_cnt)) {
                printf("%s ",current->retname);
                error("not define");
            }
            current->rettype=get_identifer_type(current->retname);
            return ;//默认是标识符
        }
        else error("in iden_or_func");
    }
    else error("in iden_or_func");
}//生成call函数代码
void if_expr(_if *tmp){
    domain_cnt++;
    if(!strcmp(str,"if")){
        NEXT;
        if(mark==LSMLBREAKET){
            NEXT;
            tmp->begin.push_back(instruction_cnt);
            gene_head_if(expr()->retname,tmp);
            delete_tmp();
            if(mark==RSMLBREAKET){

                NEXT;
                if(mark==LBIGBRACKET){
                    //printf("ok\n");

                    NEXT;
                    //printf("im in\n");
                    if_stack.push(tmp);
                    code_block();
                    if(mark==RBIGBRACKET){
                        //gene_del(function_cnt,domain_cnt);
                        domain_cnt--;
                        NEXT;
                        if(!strcmp(str,"else")){
                            NEXT;
                            if(!strcmp(str,"if")){
                                tmp=if_stack.top();
                                gene_tail_if(tmp);

                                if_stack.pop();
                                if_expr(tmp);
                            }
                            else if(mark==LBIGBRACKET){
                                gene_tail_if(tmp);
                                tmp=if_stack.top();
                                tmp->begin.push_back(instruction_cnt);
                                domain_cnt++;
                                NEXT;
                                code_block();

                                if(mark==RBIGBRACKET){
                                    tmp=if_stack.top();

                                    gene_end_if(tmp);
                                    if_stack.pop();
                                    delete(tmp);
                                    //gene_del(function_cnt,domain_cnt);
                                    domain_cnt--;
                                    NEXT;
                                    return ;
                                }
                                else error("in if_expr\n");
                            }
                            else error("in if_expr\n");
                        }
                        else{
                            tmp=if_stack.top();
                            gene_end_if(tmp);
                            if_stack.pop();
                            delete(tmp);
                        }
                    }
                    else error("in if_expr\n");
                }
                else error("in if_expr\n");
            }
            else error("in if_expr\n");
        }
        else error("in if_expr\n");
    }
}
void ret(){
    if(!strcmp(str,"return")){
        NEXT;
        int type=get_function_type(func_name);
        if(mark==IDENTIFIER||mark==NUM){
            auto p=expr();
            if(p->rettype!=type){
                if((type==_INT||type==_LONG)&&p->rettype==NUM);//modify
                else error("return type not same in %s\n",func_name);
            }
            gene_return(p->retname);
            delete_tmp();
        }
        else if(mark==SEMICOLON)
        {
            if(type==_INT||type==_LONG) {// modify
                error("no return type in %s\n",func_name);
            }
            gene_return(NULL);
        }
        else error("in return");
    }
    else error("in return");
}
void for_expr(){
    domain_cnt++;
    if(!strcmp(str,"for")){
        NEXT;
        if(mark==LSMLBREAKET){
            NEXT;
            if(mark==IDENTIFIER||mark==TYPE||mark==SEMICOLON) {
                sentence();
                if(mark==SEMICOLON){
                    NEXT;
                    _for *tmp=new _for;
                    tmp->type=FOR;
                    tmp->begin=instruction_cnt;
                    gene_head_for(expr()->retname,tmp);
                    delete_tmp();
                    if(mark==SEMICOLON){
                        NEXT;
                        if(mark==IDENTIFIER){
                            tmp->expr3=instruction_cnt;
                            expr();
                            gene_mid_for(tmp);
                            delete_tmp();
                            if(mark==RSMLBREAKET){
                                NEXT;
                                if(mark==LBIGBRACKET) {
                                    NEXT;
                                    loop_stack.push((loop*)tmp);
                                    code_block();
                                    if(mark==RBIGBRACKET){

                                        tmp=(_for*)loop_stack.top();
                                        gene_tail_for(tmp);
                                        delete tmp;
                                        loop_stack.pop();

                                        domain_cnt--;

                                        NEXT;
                                    }
                                    else error("in for...\n");
                                }
                                else error("in for...\n");
                            }
                            else error("in for...\n");
                        }
                        else if(mark==LSMLBREAKET){
                            tmp->expr3=instruction_cnt;
                            gene_mid_for(tmp);
                            NEXT;
                            if(mark==LBIGBRACKET) {
                                NEXT;
                                code_block();
                                if(mark==RBIGBRACKET){
                                    gene_del(function_cnt,domain_cnt);
                                    domain_cnt--;
                                    NEXT;
                                }
                                else error("in for...\n");
                            }
                            else error("in for...\n");
                        }
                        else error("in for...\n");
                    }
                    else error("in for...\n");
                }
                else error("in for...\n");
            }
            else error("in for...\n");

        }
        else error("in for...\n");
    }
    else error("in for...\n");
}
void while_expr(){
    domain_cnt++;
    _while *tmp=new _while;
    tmp->type=WHILE;
    tmp->begin=instruction_cnt;
    if(!strcmp(str,"while")){
        NEXT;
        if(mark==LSMLBREAKET){
            NEXT;
            char *retname=expr()->retname;
            gene_head_while(retname,tmp);
            delete_tmp();
            loop_stack.push((loop*)tmp);
            if(mark==RSMLBREAKET){
                NEXT;
                if(mark==LBIGBRACKET){
                    NEXT;
                    code_block();
                    if(mark==RBIGBRACKET){
                        tmp=(_while*)loop_stack.top();
                        gene_tail_while(tmp);
                        delete tmp;
                        loop_stack.pop();
                        domain_cnt--;
                        NEXT;
                    }
                    else error("in while\n");
                }
                else error("in while\n");
            }
            else error("in while\n");
        }
        else error("in while\n");
    }
    else error("in while\n");
}
void code_block(){
    //printf("im in\n");
    if(mark==TYPE||mark==IDENTIFIER||mark==SEMICOLON||mark==LSMLBREAKET){
        sentence();
        if(mark==SEMICOLON){
            NEXT;
            code_block();
        }
    }
    else if(mark==RESERVER){
        if(!strcmp(str,"return")){
            ret();
            if(mark==SEMICOLON){
                NEXT;
                code_block();
            }
        }
        if(!strcmp(str,"for")){
            isloop++;
            for_expr();
            isloop--;
            //printf("sadfasdf  %d \n",isloop);
            code_block();
        }
        else if(!strcmp(str,"while")){
            isloop++;
            while_expr();
            isloop--;
            code_block();
        }
        else if(!strcmp(str,"if")){
            auto tmp=new _if;
            if_expr(tmp);
            code_block();
        }
        else if(!strcmp(str,"continue")||!strcmp(str,"break")){
            //printf("isloop = %d\n",isloop);
            if(!isloop) error("no loop");
            if(!strcmp(str,"continue")){
                gene_continue();
            }
            else{
                gene_break();
            }
            NEXT;
            if(mark==SEMICOLON){
                NEXT;
                code_block();
            }
        }
    }
    else if(mark==LBIGBRACKET) {
        NEXT;
        domain_cnt++;
        code_block();
        gene_del(function_cnt,domain_cnt);
        domain_cnt--;
        if(mark==RBIGBRACKET){
            NEXT;
            code_block();
        }
        else error("expect }");
    }
}
