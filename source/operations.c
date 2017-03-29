#include "operations.h"

int or(int num1, int num2){
    if(num1== 1 | num2==1) return 1;
    return 0;
}

int and(int num1, int num2){
    if(num1== 1 && num2==1) return 1;
    return 0;
}

int exclusiveOr(int num1, int num2){
    if (num1!=num2) return 1;
    return 0;
}

int implication(int num1, int num2){
    return(!num1 || num2);
}

int equal(int num1, int num2){
    if(num1==num2) return 1;
    return 0;
}

int negate(int num1){
    if(num1==1)return 0;
    return 1;
}