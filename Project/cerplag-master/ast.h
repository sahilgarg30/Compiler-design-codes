#ifndef H_AST
#define H_AST

#include <stdio.h>
#include "ast_defs.h"

extern int ast_node_count;
extern int ast_mem_allocd;

void complain_ast_node_type(const char* funcname, astn_t node_type);

pAstNode get_ast_node(astn_t node_type);
pAstNode get_next_ast_node(pAstNode p);
int get_scope_beg_line(pAstNode p);
int get_scope_end_line(pAstNode p);
void print_ast(FILE* fp, pAstNode p, int indent);
void destroy_ast(pAstNode p);

#endif  // H_AST
