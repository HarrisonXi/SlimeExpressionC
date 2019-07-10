//
//  SLMExpression.h
//  SlimeExpression
//
//  Created by HarrisonXi on 2019/6/27.
//  Copyright © 2019 harrisonxi.com. All rights reserved.
//

#ifndef SLMExpression_h
#define SLMExpression_h

#include <stdio.h>

enum {
    SLM_EXPRESSION_ERROR_NONE = 0,
    SLM_EXPRESSION_ERROR_EXPECT_DIGIT,
    SLM_EXPRESSION_ERROR_DIVISION_BY_ZERO,
    SLM_EXPRESSION_ERROR_REMAINDER_BY_ZERO,
    SLM_EXPRESSION_ERROR_EXPECT_CLOSE_PARENTHESIS,
    SLM_EXPRESSION_ERROR_EXPECT_END,
    SLM_EXPRESSION_ERROR_UNKNOW_TOKEN,
};

int slm_eval(const char *expStr, int *errType);

#endif /* SLMExpression_h */
