//
//  main.m
//  SlimeExpression
//
//  Created by HarrisonXi on 2019/6/27.
//  Copyright © 2019 harrisonxi.com. All rights reserved.
//

#import <stdio.h>
#import "SLMExpression.h"

void test(const char *expStr) {
    int errType;
    int result = slm_eval(expStr, &errType);
    switch (errType) {
        case SLM_EXPRESSION_ERROR_NONE:
            printf("%s = %d\n", expStr, result);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_DIGIT:
            printf("%s: error - expect digit\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_DIVISION_BY_ZERO:
            printf("%s: error - division by zero\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_REMAINDER_BY_ZERO:
            printf("%s: error - remainder by zero\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_OPEN_PARENTHESIS:
            printf("%s: error - expect '('\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_CLOSE_PARENTHESIS:
            printf("%s: error - expect ')'\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_ID:
            printf("%s: error - expect ID\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_COMMA:
            printf("%s: error - expect comma\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_UNKNOW_FUNCTION:
            printf("%s: error - unknown function\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_END:
            printf("%s: error - expect end\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_UNKNOW_TOKEN:
            printf("%s: error - unknown token\n", expStr);
            break;
        default:
            printf("%s: unknown error\n", expStr);
            break;
    }
}

int main(int argc, const char * argv[]) {
    test("1    +    2");
    test("3-2+10");
    test("2 *\t\t3");
    test("3+4/2-10");
    test("1 * 2 + 3 % 2");
    test("2*2*2-30");
    test("(2 + 4) / 3");
    test("(10+2)*(20+2)");
    test("(1 + 3 * 2) % 3");
    test("10+)");
    test("1 / 0");
    test("10%0");
    test("(2 + 3 * 4");
    test("10+2)");
    test("2 * -3");
    test("10--12");
    test("1?");
    test("max(1, 2) * 2");
    test("abs(-2) * 2");
    test("max(2) * 2");
    test("fun1(2) * 2");
    return 0;
}
