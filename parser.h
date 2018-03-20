//
// Created by jason on 3/14/18.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "semantic.h"
#include "generate.h"
#define NEXT mark=get_next_token()


//  S->functionC
//  C->S|e
//  function->type identifier(argument_list){code_block}
//  argument_list->type identifier _argument_list|e
//  _argument_list->, identifier _argument_list|e
//  code_block->sentence;code_block|for_expr code_block|while_expr code_block
//           |if_expr code_block|ret;code_block|break;code_block|continue;code_block|{code_block}code_block
//  sentence->expr|statement|e



// code_block->{code_block}

//  statement->type identifier equal X
//  X->,identifier equal X|e
//  equal-> = expr |e

//  iden_or_func_or_array->identifier func|identifier |identifer array
//  array->[expr]_array
//  _array->[expr]_array|e
//




//  func->(real_argument_list)|e
//  real_argument_list->expr _real_argument_list|e
//  _real_argument_list->,expr _real_argument_list|e
//  for_expr->(sentence;expr;expr|e){code_block}
//  while_expr->(expr){code_block}
//  if_expr->if(expr){code_block}|if(expr)else if_expr|if(expr)else{code_block}
//  ret->return expr|return

//二元表达式
void test();
expr_node* expr();
void _A();
void _A_();
void _B();
void _B_();
void _C();
void _C_();
void _D();
void _D_();
void _E();
void _E_();
void _F();
void _F_();
void _G();
void _G_();
void _H();
void _H_();
void _I();
void _I_();
void _J();
void _J_();
void _K();
void _K_();
void _L();
void _L_();
void _M();//node

//
void parser();
void S();//begin
void C();
void function();//function statement or defination
void argument_list(std::vector<int>&);//
void _argument_list(std::vector<int>&);


void sentence();
void X(int );
void statement();
void equal(int ,const char *);

void iden_or_func();
void func(const char *function_name);
void real_argument_list(std::vector<int>&);
void _real_argument_list(std::vector<int>&);

void ret();
void if_expr(_if *);
void while_expr();
void for_expr();
void code_block();





#endif //COMPILER_PARSER_H
