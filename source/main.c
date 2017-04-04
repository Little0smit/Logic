#include "functions.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
/*
 *Flag1 = Algebraic equation;
 *Flag2 = Logic Solver
 *Flag3 = Categories
 * */
int main(int argc, char* argv[]) {
    int numVariables  = strtol(argv[1],NULL,10);
    char *function  = argv[2];
    char flag1 = 0;
    char flag2 = 0;
    char flag3 = 0;
    if(argc > 3) {
         flag1 = *argv[3];
         flag2 = *argv[4];
         flag3 = *argv[5];
    }
    int rows = powInt(2,(numVariables));
    if (flag1==1) {
        function = ParseInput(function);
    }
    printTableHeader(numVariables, function);
    int valid = 1, satisfied = 0;
    int result;
    for(int c=0;c<rows;c++){
        result = printTableRow(c,(numVariables),function,flag2);
        if(flag3=='1'){
            if (result==1){
                satisfied= 1;
            }else{
                valid = 0;
            }
        }
    }
    if(flag3=='1'){
        printf("The formula is ");
        if (valid){printf("valid and ");} else {printf("invalid and ");}
        if(satisfied){printf("satisfied.\n");} else {printf("unsatisfied.\n");}
    }
}
