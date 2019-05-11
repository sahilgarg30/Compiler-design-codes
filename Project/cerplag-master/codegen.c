#include <stdbool.h>
#include "ast.h"
#include "ircode.h"
#include "codegen.h"
#include "error.h"

bool allow_codegen = true;

int label_counter = 1;

void codegen_chain(pAstNode p, IRCode* irc) {
    while(p != NULL) {
        ircode_combine(irc, irc, &(p->base.ircode));
        p = get_next_ast_node(p);
    }
}

void destroy_code_chain(pAstNode p) {
    while(p != NULL) {
        ircode_clear(&(p->base.ircode));
        p = get_next_ast_node(p);
    }
}

void codegen(pAstNode p) {
    if(error_count == 0 && allow_codegen) {
        switch(p->base.node_type) {
            case ASTN_Module: {
                ModuleNode* q = (ModuleNode*)p;
                codegen_chain(q->body, &(q->base.ircode));
                break;
            }

            case ASTN_Var:
            case ASTN_Num:
            case ASTN_RNum:
            case ASTN_Bool:
                break;
            case ASTN_Decl:
            case ASTN_Deref:
                break;

            case ASTN_Assn: {
                AssnNode* q = (AssnNode*)p;
                ircode_copy(&(q->base.ircode), &(q->expr->base.ircode));
                ircode_append(&(q->base.ircode), irinstr_new2(OP_MOV, q->target->base.addr,
                    q->expr->base.addr, NULL));
                break;
            }
            case ASTN_BOp: {
                BOpNode* q = (BOpNode*)p;
                ircode_combine(&(q->base.ircode), &(q->arg1->base.ircode), &(q->arg2->base.ircode));
                ircode_append(&(q->base.ircode), irinstr_new2(q->op, q->base.addr,
                    q->arg1->base.addr, q->arg2->base.addr));
                break;
            }

            case ASTN_UOp: {
                UOpNode* q = (UOpNode*)p;
                ircode_copy(&(q->base.ircode), &(q->arg->base.ircode));
                ircode_append(&(q->base.ircode), irinstr_new2(OP_UMINUS, q->base.addr,
                    q->arg->base.addr, NULL));
                break;
            }
            case ASTN_Output: {
                OutputNode* q = (OutputNode*)p;
                ircode_append(&(q->base.ircode), irinstr_new2(OP_OUTPUT, NULL, q->var->base.addr, NULL));
                break;
            }
            case ASTN_Input: {
                InputNode* q = (InputNode*)p;
                ircode_append(&(q->base.ircode), irinstr_new2(OP_INPUT, q->base.addr, NULL, NULL));
                break;
            }
            case ASTN_For: {
                ForNode* q = (ForNode*)p;
                ircode_append(&(q->base.ircode), irinstr_new2(OP_MOV, q->base.addr, q->beg_addr, NULL));
                IRInstr* beg_instr = irinstr_new3(OP_LABEL, label_counter++);
                IRInstr* end_instr = irinstr_new3(OP_LABEL, label_counter++);
                IRInstr* break_instr = irinstr_new4(OP_JG, NULL, q->base.addr,
                    q->end_addr, end_instr->label);
                IRInstr* loop_instr = irinstr_new3(OP_JUMP, beg_instr->label);

                ircode_append(&(q->base.ircode), beg_instr);
                ircode_append(&(q->base.ircode), break_instr);
                codegen_chain(q->body, &(q->base.ircode));
                ircode_append(&(q->base.ircode), irinstr_new2(OP_INC, q->base.addr, NULL, NULL));
                ircode_append(&(q->base.ircode), loop_instr);
                ircode_append(&(q->base.ircode), end_instr);
                break;
            }
            case ASTN_While: {
                WhileNode* q = (WhileNode*)p;
                IRInstr* beg_instr = irinstr_new3(OP_LABEL, label_counter++);
                IRInstr* end_instr = irinstr_new3(OP_LABEL, label_counter++);
                IRInstr* break_instr = irinstr_new4(OP_JUMP0, NULL, q->cond->base.addr, NULL, end_instr->label);
                IRInstr* loop_instr = irinstr_new3(OP_JUMP, beg_instr->label);

                ircode_append(&(q->base.ircode), beg_instr);
                ircode_combine(&(q->base.ircode), &(q->base.ircode), &(q->cond->base.ircode));
                ircode_append(&(q->base.ircode), break_instr);
                codegen_chain(q->body, &(q->base.ircode));
                ircode_append(&(q->base.ircode), loop_instr);
                ircode_append(&(q->base.ircode), end_instr);
                break;
            }
            case ASTN_Switch: {
                SwitchNode* q = (SwitchNode*)p;
                CaseNode* node;
                if(q->base.addr->type == TYPE_BOOLEAN) {
                    pAstNode true_stmts=NULL, false_stmts=NULL;
                    for(node = q->cases; node != NULL; node = node->next) {
                        bool val = ((BoolNode*)(node->val))->val;
                        if(val) true_stmts = node->stmts;
                        else false_stmts = node->stmts;
                    }
                    IRInstr* label1 = irinstr_new3(OP_LABEL, label_counter++);
                    IRInstr* label2 = irinstr_new3(OP_LABEL, label_counter++);
                    ircode_append(&(q->base.ircode), irinstr_new4(OP_JUMP0,
                        NULL, q->base.addr, NULL, label1->label));
                    codegen_chain(true_stmts, &(q->base.ircode));
                    ircode_append(&(q->base.ircode), irinstr_new3(OP_JUMP, label2->label));
                    ircode_append(&(q->base.ircode), label1);
                    codegen_chain(false_stmts, &(q->base.ircode));
                    ircode_append(&(q->base.ircode), label2);
                }
                else {
                    IRInstr* exit_label = irinstr_new3(OP_LABEL, label_counter++);
                    for(node = q->cases; node != NULL; node = node->next) {
                        IRInstr* label = irinstr_new3(OP_LABEL, label_counter++);
                        ircode_append(&(q->base.ircode), irinstr_new4(OP_JNE,
                            NULL, q->base.addr, node->val->base.addr, label->label));
                        codegen_chain(node->stmts, &(q->base.ircode));
                        ircode_append(&(q->base.ircode), irinstr_new3(OP_JUMP, exit_label->label));
                        ircode_append(&(q->base.ircode), irinstr_new3(OP_LABEL, label->label));
                    }
                    if(q->defaultcase != NULL) {
                        codegen_chain(q->defaultcase->stmts, &(q->base.ircode));
                    }
                    ircode_append(&(q->base.ircode), irinstr_new3(OP_LABEL, exit_label->label));
                }
                break;
            }
            default:
                complain_ast_node_type(__func__, p->base.node_type);
        }
    }
    if(error_count > 0) {
        switch(p->base.node_type) {
            case ASTN_BOp:
                ircode_clear(&(((BOpNode*)p)->arg1->base.ircode));
                ircode_clear(&(((BOpNode*)p)->arg2->base.ircode));
                break;
            case ASTN_UOp:
                ircode_clear(&(((UOpNode*)p)->arg->base.ircode));
                break;
            case ASTN_Deref:
                ircode_clear(&(((DerefNode*)p)->index->base.ircode));
                break;
            case ASTN_Module:
                destroy_code_chain(((ModuleNode*)p)->body);
                break;
            case ASTN_Assn:
                ircode_clear(&(((AssnNode*)p)->target->base.ircode));
                ircode_clear(&(((AssnNode*)p)->expr->base.ircode));
                break;
            case ASTN_While:
                ircode_clear(&(((WhileNode*)p)->cond->base.ircode));
                ircode_clear(&(((WhileNode*)p)->body->base.ircode));
                break;
            case ASTN_For:
                ircode_clear(&(((ForNode*)p)->body->base.ircode));
                break;
            case ASTN_Decl:
                destroy_code_chain((pAstNode)(((DeclNode*)p)->idList));
                break;
            case ASTN_Output:
                ircode_clear(&(((OutputNode*)p)->var->base.ircode));
                break;
            case ASTN_FCall:
                destroy_code_chain((pAstNode)(((FCallNode*)p)->iParamList));
                destroy_code_chain((pAstNode)(((FCallNode*)p)->oParamList));
                break;
            case ASTN_Switch: {
                SwitchNode* q = (SwitchNode*)p;
                if(q->defaultcase != NULL) {
                    ircode_clear(&(q->defaultcase->val->base.ircode));
                    destroy_code_chain(q->defaultcase->stmts);
                }
                CaseNode* node = q->cases;
                while(node != NULL) {
                    destroy_code_chain(node->stmts);
                    ircode_clear(&(node->val->base.ircode));
                    node = node->next;
                }
                break;
            }
            default:
                break;
        }
    }
    /*
    fprintf(stderr, "codegen on node(%s, %d:%d):\n", ASTN_STRS[p->base.node_type], p->base.line, p->base.col);
    ircode_print(&(p->base.ircode), stderr);
    */
}

void optimize_ircode(IRCode* code) {
    IRInstr* instr = code->first;
    IRInstr* instr2 = NULL;
    for(; instr != NULL; instr = instr2) {
        instr2 = instr->next;
        while(instr2 != NULL && instr->res != NULL && instr->res->addr_type == ADDR_TEMP && instr2->op == OP_MOV) {
            instr->res = instr2->res;
            instr2 = instr2->next;
            ircode_remove(code, instr->next);
        }
    }
}
