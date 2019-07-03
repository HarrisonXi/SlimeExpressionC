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
    printf("%s=%d\n", expStr, slm_eval(expStr));
}

int main(int argc, const char * argv[]) {
    test("1+2");
    test("3-2+1");
    test("2*3");
    test("3+4/2-1");
    test("1*2+3%2");
    test("2*2*2-3");
    return 0;
}
