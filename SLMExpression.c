//
//  SLMExpression.c
//  SlimeExpression
//
//  Created by HarrisonXi on 2019/6/27.
//  Copyright © 2019 harrisonxi.com. All rights reserved.
//

#include "SLMExpression.h"
#include <ctype.h>

enum {
    SLM_EXPRESSION_TOKEN_UNKNOWN = 0,
    SLM_EXPRESSION_TOKEN_DIGITS,
    SLM_EXPRESSION_TOKEN_ADD,
    SLM_EXPRESSION_TOKEN_SUB_OR_MINUS,
    SLM_EXPRESSION_TOKEN_MUL,
    SLM_EXPRESSION_TOKEN_DIV,
    SLM_EXPRESSION_TOKEN_MOD,
    SLM_EXPRESSION_TOKEN_OPEN,
    SLM_EXPRESSION_TOKEN_CLOSE,
    SLM_EXPRESSION_TOKEN_END
};

typedef struct {
    int type;
    int value;
} slm_token;

typedef struct {
    const char *expStr;
    slm_token token;
    int errType;
} slm_expr;

int expr(slm_expr *e);

#define TRY(func) func; if (e->errType) return 0;
#define THROW(error) e->errType = error; return 0;

void next(slm_expr *e) {
    while (isspace(*e->expStr)) {
        (e->expStr)++;
    }
    if (*e->expStr == 0) {
        e->token.type = SLM_EXPRESSION_TOKEN_END;
    } else if (isdigit(*e->expStr)) {
        e->token.type = SLM_EXPRESSION_TOKEN_DIGITS;
        e->token.value = *e->expStr - '0';
        (e->expStr)++;
        while (isdigit(*e->expStr)) {
            e->token.value = e->token.value * 10 + (*e->expStr - '0');
            (e->expStr)++;
        }
    } else {
        switch (*e->expStr) {
            case '+':
                e->token.type = SLM_EXPRESSION_TOKEN_ADD;
                (e->expStr)++;
                break;
            case '-':
                e->token.type = SLM_EXPRESSION_TOKEN_SUB_OR_MINUS;
                (e->expStr)++;
                break;
            case '*':
                e->token.type = SLM_EXPRESSION_TOKEN_MUL;
                (e->expStr)++;
                break;
            case '/':
                e->token.type = SLM_EXPRESSION_TOKEN_DIV;
                (e->expStr)++;
                break;
            case '%':
                e->token.type = SLM_EXPRESSION_TOKEN_MOD;
                (e->expStr)++;
                break;
            case '(':
                e->token.type = SLM_EXPRESSION_TOKEN_OPEN;
                (e->expStr)++;
                break;
            case ')':
                e->token.type = SLM_EXPRESSION_TOKEN_CLOSE;
                (e->expStr)++;
                break;
            default:
                e->token.type = SLM_EXPRESSION_TOKEN_UNKNOWN;
                e->errType = SLM_EXPRESSION_ERROR_UNKNOW_TOKEN;
                break;
        }
    }
}

int number(slm_expr *e)
{
    /*
     number = '-' digits
            | digits
     */
    int hasMinus = 0;
    if (e->token.type == SLM_EXPRESSION_TOKEN_SUB_OR_MINUS) {
        TRY(next(e));
        hasMinus = 1;
    }
    if (e->token.type != SLM_EXPRESSION_TOKEN_DIGITS) {
        THROW(SLM_EXPRESSION_ERROR_EXPECT_DIGIT);
    }
    int result = e->token.value;
    TRY(next(e));
    if (hasMinus) {
        result *= -1;
    }
    return result;
}

int factor(slm_expr *e)
{
    /*
     factor = number
            | '(' expr ')'
     */
    int result;
    if (e->token.type == SLM_EXPRESSION_TOKEN_OPEN) {
        TRY(next(e));
        result = TRY(expr(e));
        if (e->token.type != SLM_EXPRESSION_TOKEN_CLOSE) {
            THROW(SLM_EXPRESSION_ERROR_EXPECT_CLOSE_PARENTHESIS);
        }
        TRY(next(e));
    } else {
        result = TRY(number(e));
    }
    return result;
}

int term(slm_expr *e)
{
    /*
     term  = factor term1
     term1 = '*' factor term1
           | '/' factor term1
           | '%' factor term1
           | null
     */
    int result = TRY(factor(e));
    while (e->token.type == SLM_EXPRESSION_TOKEN_MUL
           || e->token.type == SLM_EXPRESSION_TOKEN_DIV
           || e->token.type == SLM_EXPRESSION_TOKEN_MOD) {
        int op = e->token.type;
        TRY(next(e));
        int f = TRY(factor(e));
        if (op == SLM_EXPRESSION_TOKEN_MUL) {
            result *= f;
        } else if (op == SLM_EXPRESSION_TOKEN_DIV) {
            if (f == 0) {
                THROW(SLM_EXPRESSION_ERROR_DIVISION_BY_ZERO);
            }
            result /= f;
        } else {
            if (f == 0) {
                THROW(SLM_EXPRESSION_ERROR_REMAINDER_BY_ZERO);
            }
            result %= f;
        }
    }
    return result;
}

int expr(slm_expr *e)
{
    /*
     expr  = term expr1
     expr1 = '+' term expr1
           | '-' term expr1
           | null
     */
    int result = TRY(term(e));
    while (e->token.type == SLM_EXPRESSION_TOKEN_ADD || e->token.type == SLM_EXPRESSION_TOKEN_SUB_OR_MINUS) {
        int op = e->token.type;
        TRY(next(e))
        int t = TRY(term(e));
        if (op == SLM_EXPRESSION_TOKEN_ADD) {
            result += t;
        } else {
            result -= t;
        }
    }
    return result;
}

int slm_eval(const char *expStr, int *errType)
{
    slm_expr e;
    e.expStr = expStr;
    e.errType = SLM_EXPRESSION_ERROR_NONE;
    int result = 0;
    next(&e);
    if (e.errType == 0) {
        result = expr(&e);
        if (e.errType == 0 && e.token.type != SLM_EXPRESSION_TOKEN_END) {
            e.errType = SLM_EXPRESSION_ERROR_EXPECT_END;
            result = 0;
        }
    }
    if (errType) {
        *errType = e.errType;
    }
    return result;
}
