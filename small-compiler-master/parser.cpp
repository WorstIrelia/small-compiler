//
// Created by jason on 3/14/18.
//
#include "parser.h"
#include "scanner.h"
#include "error.h"
#include "semantic.h"
#include <cstring>
#include <cstdio>
#include <unordered_map>
#include <vector>

std::vector<int>argument_list_v;
static int mark;
extern int num;
extern char str[];
extern int domain_cnt;
extern int function_cnt;
extern std::unordered_map<int,int> level;

expr_node *root=new expr_node();
expr_node *current=root;


void expr(){

    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _A();
    strcpy(tmp->father->retname,tmp->retname);

}
void test(){
    NEXT;
    printf("im in\n");
    expr();
    printf("success\n");
}

void _A(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _B();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _A_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _A_(){
    if(level[hash(str)]==1){

        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _B();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _A_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}
void _B(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _C();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _B_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _B_(){
    //printf("im in _B_\n");
    if(level[hash(str)]==2){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _C();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _B_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}
void _C(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _D();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _C_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _C_(){
    if(level[hash(str)]==3){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _D();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _C_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}
void _D(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _E();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _D_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _D_(){
    if(level[hash(str)]==4){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _E();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _D_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}
void _E(){

    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _F();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _E_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _E_(){
    if(level[hash(str)]==5){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _F();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _E_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}
void _F(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _G();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _F_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _F_(){
    if(level[hash(str)]==6){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _G();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _F_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}
void _G(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _H();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;
    _G_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _G_(){
    if(level[hash(str)]==7){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _H();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _G_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}
void _H(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _I();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _H_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _H_(){
    if(level[hash(str)]==8){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _I();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _H_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}
void _I(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _J();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _I_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _I_(){
    if(level[hash(str)]==9){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _J();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _I_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}
void _J(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _K();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _J_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _J_(){
    if(level[hash(str)]==10){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _K();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;
        _J_();

        if(tmp1->retname[0]!=0) {
            printf("im in +\n");
            strcpy(tmp1->father->retname,tmp1->retname);
        }
    }
}
void _K(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _L();

    strcpy(tmp->father->retname,tmp->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _K_();
    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
}
void _K_(){
    //printf("im in _k_\n");
    if(level[hash(str)]==11){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _L();

        strcpy(tmp1->father->rname,tmp1->retname);
        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _K_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}
void _L(){
    expr_node *tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;

    _M();


    //printf("test %s\n",tmp->retname);
    strcpy(tmp->father->retname,tmp->retname);
    //printf("father test %s\n",tmp->father->retname);

    current=tmp->father;
    tmp=new expr_node;
    node_init(current,tmp);
    current=tmp;
    //printf("im in\n");
    _L_();


    if(tmp->retname[0]!=0)strcpy(tmp->father->retname,tmp->retname);
    //printf("father test2 %s\n",tmp->father->retname);
}
void _L_(){
    //printf("im in _L_\n");
    if(level[hash(str)]==12){


        strcpy(current->lname,current->father->retname);
        strcpy(current->op,str);
        NEXT;
        expr_node *tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _M();
        strcpy(tmp1->father->rname,tmp1->retname);

        char test[300];
        int cnt=0;
        int len1=strlen(tmp1->father->lname);
        int len2=strlen(tmp1->father->rname);
        for(int i=0;i<len1;i++) test[cnt++]=tmp1->father->lname[i];
        for(int i=0;i<len2;i++) test[cnt++]=tmp1->father->rname[i];
        test[cnt]=0;
        strcpy(tmp1->father->retname,test);



        current=tmp1->father;
        printf("%s %s %s %s\n",current->retname,current->lname,current->op,current->rname);


        tmp1=new expr_node;
        node_init(current,tmp1);
        current=tmp1;

        _L_();

        if(tmp1->retname[0]!=0) strcpy(tmp1->father->retname,tmp1->retname);
    }
}

void _M(){
    //printf("im in\n");
    //printf("%s\n",str);
    if(!strcmp(str,"(")){
        NEXT;

        expr_node *tmp=new expr_node;
        node_init(current,tmp);
        current=tmp;

        _A();

        strcpy(tmp->father->retname,tmp->retname);
        //printf("test %s\n",tmp->retname);
        if(!strcmp(str,")")){
            NEXT;
        }
        else error("in M");
    }
    else if(mark==NUM){
        //printf("im in mark\n");

        current->rettype=NUM;
        current->istmp=0;
        current->name[0]='n';
        current->name[1]=0;

        NEXT;
    }
    else {

        current->rettype=NUM;
        current->istmp=0;
        //printf("%s asdfasdfa\n",str);
        strcpy(current->retname,str);//默认是标识符

        NEXT;//默认是标识符
        //iden_or_func();
    }
}









//void parser(){
//    NEXT;
//    //printf("???\n");
//    S();
//    printf("success\n");
//}
//void S(){
//    //printf("im in\n");
//    if(mark==TYPE){
//        function();
//        C();
//    }
//    else{
//        error("error in S()\n");
//    }
//}
//void function(){
//    //printf("im in\n");
//
//    //fucntion analize
//    int type;
//    char name[128];
//    if(mark==TYPE){
//        type=TYPE;
//        NEXT;
//        if(mark==IDENTIFIER) {
//            strcpy(name,str);
//            NEXT;
//            if (mark == LSMLBREAKET) {
//                NEXT;
//
//                argument_list_v.clear();
//
//                argument_list();
//                if (mark == RSMLBREAKET) {
//                    NEXT;
//                    if (mark == LBIGBRACKET) {
//                        if(in_function(name)){
//                            if(!is_same_function(name,type,argument_list_v))
//                                error("chongdingyi");
//                        }
//                        add_function(name,type,argument_list_v,1,0);
//
//                        function_cnt++;
//
//                        NEXT;
//                        code_block();
//                        if (mark == RBIGBRACKET) {
//                            NEXT;
//                            return;
//                        }
//                        else error("in function,expect }\n");
//                    }
//                    else if(mark==SEMICOLON){
//
//
//                        if(in_function(name)){
//                            error("chongdingyi");
//                        }
//                        add_function(name,type,argument_list_v,0,0);
//                        NEXT;
//
//                    }
//                    else error("in function,expect {\n");
//                }
//                else error("in function,expect )\n");
//            }
//            else error("in function,expect (\n");
//        }
//        else error("in function,expect identifier\n");
//    }
//    else error("in function,expect type\n");
//}
//void _argument_list(){
//    if(mark==COMMA){
//        NEXT;
//        if(mark==TYPE){
//            argument_list_v.push_back();
//            NEXT;
//            if(mark==IDENTIFIER){
//                NEXT;
//                _argument_list();
//            }
//            else error("in _arguement_list\n");
//        }
//
//    }
//    else if(mark==RSMLBREAKET) return ;
//    else error("in _arguement_list\n");
//}
//void argument_list(){
//    if(mark==TYPE){
//        argument_list_v.push_back();
//        NEXT;
//        if(mark==IDENTIFIER){
//            NEXT;
//            if(mark==COMMA) {
//                _argument_list();
//            }
//            else if(mark==RSMLBREAKET) return;
//            else error("in arguement_list,expect ,\n");
//        }
//        else error("in arguement_list,expect identifier\n");
//    }
//    else if(mark==RSMLBREAKET) return;
//    else error("in arguement_list,expect type or )\n");
//}
//void sentence(){
//    if(mark==TYPE){
//        statement();
//    }
//    else if(mark==IDENTIFIER){
//        expr();
//    }
//    else error("in sentence\n");
//}
//void statement(){
//    char name[128];
//    int type;
//    if(mark==TYPE){
//        type=TYPE;
//        NEXT;
//        if(mark==IDENTIFIER){
//            strcpy(name,str);
//
//            add(str,type,function_cnt,domain_cnt);
//
//            NEXT;
//            equal();
//            X();
//        }
//        else error("in statement,expect identifier\n");
//    }
//    else error("in statement,expect type\n");
//}
//void X(){
//    if(mark==COMMA){
//        NEXT;
//        if(mark==IDENTIFIER){
//            add(str,gettype,function_cnt,domain_cnt);
//            NEXT;
//            equal();
//            X();
//        }
//        else error("in X,expect identifier\n");
//    }
//    else if(mark==SEMICOLON) return;
//    else error("in X,expect , or ;\n");
//}
//void ret(){
//    if(!strcmp(str,"return")){
//        NEXT;
//        if(mark==IDENTIFIER||mark==NUM){
//            expr();
//        }
//        else if(mark==SEMICOLON) return;
//        else error("in return");
//    }
//    else error("in return");
//}







//void calcu_expr(){
//    if(mark==NUM||mark==IDENTIFIER){
//        if(mark==IDENTIFIER){
//            iden_or_func();
//        }
//        else if(mark==NUM){
//            NEXT;
//        }
//        if(mark=='+'||mark=='-'){
//            _calcu_expr();
//        }
//        else if(mark=='<'||mark=='>'||mark==';'||mark==')') return ;
//
//        else error("in calcu_expr\n");
//    }
//    else error("in calcu_expr,expect identifier or number\n");
//}
//void _calcu_expr(){
//    if(mark=='+'||mark=='-'){
//        NEXT;
//        if(mark==IDENTIFIER||mark==NUM){
//            if(mark==IDENTIFIER){
//                iden_or_func();
//            }
//            else if(mark==NUM){
//
//                NEXT;
//            }
//            _calcu_expr();
//        }
//        else error("in _calcu_expr");
//    }
//    else if(mark==';'||mark==')') return ;
//    else error("in _calcu_expr,expect operator or ;\n");
//}
//void logical_expr(){
//    if(mark==IDENTIFIER||mark==NUM){
//        //printf("im in\n");
//        calcu_expr();
//        if(mark=='<'||mark=='>'){
//            NEXT;
//            //printf("im in");
//            if(mark==IDENTIFIER||mark==NUM){
//
//                calcu_expr();
//            }
//            else error("in logical_expr,expect identifier\n");
//        }
//        else error("in logical_expr,expect < or >\n");
//    }
//    else error("in logical_expr,expect identifier\n");
//}






//void equal(){
//    if(!strcmp(str,"=")){
//        NEXT;
//        expr();
//    }
//    else return ;
//}
//void code_block(){
//    if(mark==TYPE||mark==IDENTIFIER){
//        sentence();
//        if(mark==SEMICOLON){
//            NEXT;
//            code_block();
//        }
//    }
//    else if(mark==RESERVER){
//        if(!strcmp(str,"return")){
//            ret();
//            if(mark==SEMICOLON){
//                NEXT;
//                code_block();
//            }
//        }
//        if(!strcmp(str,"for")){
//            for_expr();
//            code_block();
//        }
//        else if(!strcmp(str,"while")){
//            while_expr();
//            code_block();
//        }
//        else if(!strcmp(str,"if")){
//            if_expr();
//            code_block();
//        }
//        else if(!strcmp(str,"continue")||!strcmp(str,"break")){
//            NEXT;
//            if(mark==SEMICOLON){
//                NEXT;
//                code_block();
//            }
//        }
//    }
//    else if(mark==RBIGBRACKET) return ;
//    else error("in code_blocks,expect ;\n");
//}
//void C(){
//    //printf("CCCC\n");
//    if(mark==EOF){
//        return;
//    }
//    else if(mark==TYPE){
//        S();
//    }
//    else error("in C,expect type\n");
//}
//void real_argument_list(){
//    if(mark==RSMLBREAKET) return;
//    else if(mark==IDENTIFIER||mark==NUM){
//        expr();
//        _real_argument_list();
//    }
////    else if(mark==IDENTIFIER||mark==NUM){
////        calcu_expr();
////        _real_argument_list();
////    }
//}
//void _real_argument_list(){
////    if(mark==','){
////        calcu_expr();
////        _real_argument_list();
////    }
//    if(mark==COMMA){
//        NEXT;
//        //calcu_expr();
//        expr();
//        _real_argument_list();
//    }
//    else if(mark==RSMLBREAKET) return ;
//    else error("in _real_argument_list");
//}
//void func(){
//    if(mark==LSMLBREAKET){
//        NEXT;
//        //printf("im in func\n");
//        real_argument_list();//
//        if(mark==RSMLBREAKET){
//            NEXT;
//            return;
//        }
//        else error("in func");
//    }
//    else error("in func");
//}
//void iden_or_func(){
//    //printf("im in\n");
//    if(mark==IDENTIFIER){
//        NEXT;
//        //printf("im in aaaaa\n");
//        if(mark==LSMLBREAKET){
//            func();
//            return ;
//        }
//        else if(mark==OPERATOR||mark==RSMLBREAKET||mark==SEMICOLON||mark==COMMA) return;//右边小括号 还有别的情况
//        else error("in iden_or_func");
//    }
//    else error("in iden_or_func");
//}
//void for_expr(){
//    if(!strcmp(str,"for")){
//        NEXT;
//        if(mark==LSMLBREAKET){
//            NEXT;
//            if(mark==IDENTIFIER||mark==TYPE) {
//                if(mark==IDENTIFIER) expr();
//                else statement();
//                if(mark==SEMICOLON){
//                    NEXT;
//                    expr();
//                    if(mark==SEMICOLON){
//                        NEXT;
//                        if(mark==IDENTIFIER){
//                            expr();
//                            if(mark==RSMLBREAKET){
//                                NEXT;
//                                if(mark==LBIGBRACKET) {
//                                    NEXT;
//                                    code_block();
//                                    if(mark==RBIGBRACKET){
//                                        NEXT;
//                                        code_block();
//                                    }
//                                    else error("in for...\n");
//                                }
//                                else error("in for...\n");
//                            }
//                            else error("in for...\n");
//                        }
//                        else if(mark==LSMLBREAKET){
//                            NEXT;
//                            if(mark==LBIGBRACKET) {
//                                NEXT;
//                                code_block();
//                                if(mark==RBIGBRACKET){
//                                    NEXT;
//                                    code_block();
//                                }
//                                else error("in for...\n");
//                            }
//                            else error("in for...\n");
//                        }
//                        else error("in for...\n");
//                    }
//                    else error("in for...\n");
//                }
//                else error("in for...\n");
//            }
//            else if(mark==SEMICOLON){
//                NEXT;
//                expr();
//                if(mark==SEMICOLON){
//                    NEXT;
//                    if(mark==IDENTIFIER){
//                        expr();
//                        if(mark==RSMLBREAKET){
//                            NEXT;
//                            if(mark==LBIGBRACKET) {
//                                NEXT;
//                                code_block();
//                                if(mark==RBIGBRACKET){
//                                    NEXT;
//                                    code_block();
//                                }
//                                else error("in for...\n");
//                            }
//                            else error("in for...\n");
//                        }
//                        else error("in for...\n");
//                    }
//                    else if(mark==RSMLBREAKET){
//                        NEXT;
//                        if(mark==LBIGBRACKET) {
//                            NEXT;
//                            code_block();
//                            if(mark==RBIGBRACKET){
//                                NEXT;
//                                code_block();
//                            }
//                            else error("in for...\n");
//                        }
//                        else error("in for...\n");
//                    }
//                    else error("in for...\n");
//                }
//                else error("in for...\n");
//            }
//            else error("in for...\n");
//
//        }
//        else error("in for...\n");
//    }
//    else error("in for...\n");
//}
//void while_expr(){
//    if(!strcmp(str,"while")){
//        NEXT;
//        if(mark==LSMLBREAKET){
//            NEXT;
//            expr();
//            if(mark==RSMLBREAKET){
//                NEXT;
//                if(mark==LBIGBRACKET){
//
//                    NEXT;
//                    code_block();
//                    if(mark==RBIGBRACKET){
//                        NEXT;
//                        code_block();
//                    }
//                    else error("in while\n");
//                }
//                else error("in while\n");
//            }
//            else error("in while\n");
//        }
//        else error("in while\n");
//    }
//    else error("in while\n");
//}
//void if_expr(){
//    if(!strcmp(str,"if")){
//        NEXT;
//        if(mark==LSMLBREAKET){
//            NEXT;
//            expr();
//            if(mark==RSMLBREAKET){
//                NEXT;
//                if(mark==LBIGBRACKET){
//                    NEXT;
//                    //printf("im in\n");
//                    code_block();
//                    if(mark==RBIGBRACKET){
//                        NEXT;
//                        if(!strcmp(str,"else")){
//                            NEXT;
//                            if(!strcmp(str,"if")){
//                                if_expr();
//                            }
//                            else if(mark==LBIGBRACKET){
//                                NEXT;
//                                code_block();
//                                if(mark==RBIGBRACKET){
//                                    NEXT;
//                                    return ;
//                                }
//                                else error("in if_expr\n");
//                            }
//                            else error("in if_expr\n");
//                        }
//                    }
//                    else error("in if_expr\n");
//                }
//                else error("in if_expr\n");
//            }
//            else error("in if_expr\n");
//        }
//        else error("in if_expr\n");
//    }
//}