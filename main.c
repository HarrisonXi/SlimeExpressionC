//
//  main.m
//  SlimeExpression
//
//  Created by HarrisonXi on 2019/6/27.
//  Copyright © 2019 harrisonxi.com. All rights reserved.
//

#import <stdio.h>
#import "SLMExpression.h"

int main(void) {
    printf("1+2=%d\n", slm_eval("1+2"));
    printf("1-2+3=%d\n", slm_eval("1-2+3"));
    return 0;
}
