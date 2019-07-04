//
//  SLMExpression.c
//  SlimeExpression
//
//  Created by HarrisonXi on 2019/6/27.
//  Copyright © 2019 harrisonxi.com. All rights reserved.
//

#include "SLMExpression.h"

int expr(const char **expStr);

int number(const char **expStr)
{
    /*
     number = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
     */
    int result = **expStr - '0';
    (*expStr)++;
    return result;
}

int factor(const char **expStr)
{
    /*
     factor = number
            | '(' expr ')'
    */
    int result;
    if (**expStr == '(') {
        (*expStr)++;
        result = expr(expStr);
        if (**expStr == ')') {
            (*expStr)++;
        }
    } else {
        result = number(expStr);
    }
    return result;
}

int term(const char **expStr)
{
    /*
     term  = factor term1
     term1 = '*' factor term1
           | '/' factor term1
           | '%' factor term1
           | null
     */
    int result = factor(expStr);
    while (**expStr == '*' || **expStr == '/' || **expStr == '%') {
        char op = **expStr;
        (*expStr)++;
        if (op == '*') {
            result *= factor(expStr);
        } else if (op == '/') {
            result /= factor(expStr);
        } else {
            result %= factor(expStr);
        }
    }
    return result;
}

int expr(const char **expStr)
{
    /*
     expr  = term expr1
     expr1 = '+' term expr1
           | '-' term expr1
           | null
     */
    int result = term(expStr);
    while (**expStr == '+' || **expStr == '-') {
        char op = **expStr;
        (*expStr)++;
        if (op == '+') {
            result += term(expStr);
        } else {
            result -= term(expStr);
        }
    }
    return result;
}

int slm_eval(const char *expStr)
{
    return expr(&expStr);
}
