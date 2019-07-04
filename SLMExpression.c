//
//  SLMExpression.c
//  SlimeExpression
//
//  Created by HarrisonXi on 2019/6/27.
//  Copyright © 2019 harrisonxi.com. All rights reserved.
//

#include "SLMExpression.h"

typedef struct {
    const char *expStr;
    int errType;
} slm_expr;

int expr(slm_expr *e);

#define TRY(func) func; if (e->errType) return 0;
#define THROW(error) e->errType = error; return 0;

int number(slm_expr *e)
{
    /*
     number = '-' digit
            | digit
     digit  = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
     */
    int hasMinus = 0;
    if (*e->expStr == '-') {
        (e->expStr)++;
        hasMinus = 1;
    }
    if (*e->expStr < '0' || *e->expStr > '9') {
        THROW(SLM_EXPRESSION_ERROR_TYPE_EXPECT_DIGIT);
    }
    int result = *e->expStr - '0';
    (e->expStr)++;
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
    if (*e->expStr == '(') {
        (e->expStr)++;
        result = TRY(expr(e));
        if (*e->expStr != ')') {
            THROW(SLM_EXPRESSION_ERROR_TYPE_EXPECT_CLOSE_PARENTHESIS);
        }
        (e->expStr)++;
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
    while (*e->expStr == '*' || *e->expStr == '/' || *e->expStr == '%') {
        char op = *e->expStr;
        (e->expStr)++;
        int f = TRY(factor(e));
        if (op == '*') {
            result *= f;
        } else if (op == '/') {
            if (f == 0) {
                THROW(SLM_EXPRESSION_ERROR_TYPE_DIVISION_BY_ZERO);
            }
            result /= f;
        } else {
            if (f == 0) {
                THROW(SLM_EXPRESSION_ERROR_TYPE_REMAINDER_BY_ZERO);
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
    while (*e->expStr == '+' || *e->expStr == '-') {
        char op = *e->expStr;
        (e->expStr)++;
        int t = TRY(term(e));
        if (op == '+') {
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
    e.errType = SLM_EXPRESSION_ERROR_TYPE_NONE;
    int result = expr(&e);
    if (e.errType == 0 && *e.expStr != 0) {
        e.errType = SLM_EXPRESSION_ERROR_TYPE_EXPECT_END;
        result = 0;
    }
    if (errType) {
        *errType = e.errType;
    }
    return result;
}
