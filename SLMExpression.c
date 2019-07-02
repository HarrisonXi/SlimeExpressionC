//
//  SLMExpression.c
//  SlimeExpression
//
//  Created by HarrisonXi on 2019/6/27.
//  Copyright © 2019 harrisonxi.com. All rights reserved.
//

#include "SLMExpression.h"

int number(const char *expStr)
{
    /*
     number = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
     */
    return *expStr - '0';
}

int expr(const char *expStr)
{
    /*
     expr  = number expr1
     expr1 = '+' number expr1
           | '-' number expr1
           | null
     */
    int result = number(expStr++);
    while (*expStr == '+' || *expStr == '-') {
        char op = *expStr; expStr++;
        if (op == '+') {
            result += number(expStr++);
        } else {
            result -= number(expStr++);
        }
    }
    return result;
}

int slm_eval(const char *expStr)
{
    return expr(expStr);
}
