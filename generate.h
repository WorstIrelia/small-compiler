//
// Created by jason on 3/17/18.
//

#ifndef COMPILER_GENERATE_H
#define COMPILER_GENERATE_H
#define INSTRUCTION_SIZE 32
#include <cstdio>
#include <vector>
struct loop{
    int type;
};
struct _while:loop{
    int begin;
    std::vector<int>v;
    int _false;
};
struct _for:loop{
    int begin;
    int expr3;
    int iftrue;
    int iffalse;
    std::vector<int>v;

};

struct _if{
    std::vector<int>begin;
    std::vector<int>jf;
    std::vector<int>jump;
};


char *atoi();
char *next_tmp() ;
void delete_tmp();
void mark_add(const char *str,int function,int domain);
void mark_array_add(const char *str,int function,int domain);
void gene_add(const char *);
void gene_lea(const char *,int );
void gene_two_op(const char *lname,const char *rname,const char *op,const char *tmpname);
void gene_del(int function,int domian);

void gene_real_argument(const char *);

void gene_head_if(const char *str,_if *tmp);
void gene_tail_if(_if* tmp);
void gene_end_if(_if *tmp);

void gene_head_while(const char *str,_while *);
void gene_tail_while(_while *);
void gene_head_for(const char *str,_for *tmp);
void gene_mid_for(_for *);
void gene_tail_for(_for *);
void gene_continue();
void gene_break();
void generate_all();
void gene_call_begin();
void gene_call_end(const char *,const char *);

void gene_add_array(const char *,long );
void gene_offset(const char *,const char *);
void gene_set_offset(const char *);
void gene_start();
void gene_return(const char *str);
void del(int num);
void scan();

void return_test();
#endif //COMPILER_GENERATE_H
