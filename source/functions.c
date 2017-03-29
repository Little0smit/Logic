#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "functions.h"
#include "operations.h"
#define asciOffset 48;
const char* alphabet = "abcdefghijklmnopqrstuvwxyz";

int bitValueAt(int number, int index){
    int bit;
    if (index == 0){
        bit = (number&1);
    } else {
        bit = (number >> index)&1;
    }
    return bit;
}

//Calculates x to the power of y
int powInt(int x, int y){
    int result = 1;
    while(y){
        if (y&1)
            result *= x;
        y /= 2;
        x *= x;
    }
    return result;
}
void printTableRow(int rowNumber, int numVariables, char* function){
    for(int c=numVariables-1;c>=0;c--){
        printf("%d ",bitValueAt(rowNumber,c));
    }
    printf(": ");
    solveRow(rowNumber, numVariables, function);
}

void solveRow(int rowNumber,int numVariables,char* function){
    int *stack = calloc(numVariables,sizeof(int));
    int stackHead=0;
    int stringLength = strlen(function);
    for(int c=0;c<stringLength+1;c++){
        int num1=0, num2=0;
        switch(readCharAt(c,function)) {
            case '-':
                stackHead--;
                num1 = stack[stackHead];
                stack[stackHead] = negate(num1);
                printf("%d",stack[stackHead]);
                stackHead++;
                break;
            case '|':
                stackHead--;
                num1 = stack[stackHead];
                stackHead--;
                num2 = stack[stackHead];
                stack[stackHead] = or(num1,num2);
                printf("%d",stack[stackHead]);
                stackHead++;
                break;
            case '&':
                stackHead--;
                num1 = stack[stackHead];
                stackHead--;
                num2 = stack[stackHead];
                stack[stackHead] = and(num1,num2);
                printf("%d",stack[stackHead]);
                stackHead++;
                break;
            case '#':
                stackHead--;
                num1 = stack[stackHead];
                stackHead--;
                num2 = stack[stackHead];
                stack[stackHead] = exclusiveOr(num1,num2);
                printf("%d",stack[stackHead]);
                stackHead++;
                break;
            case '>':
                stackHead--;
                num2 = stack[stackHead];
                stackHead--;
                num1 = stack[stackHead];
                stack[stackHead] = implication(num1,num2);
                printf("%d",stack[stackHead]);
                stackHead++;
                break;
            case '=':
                stackHead--;
                num1 = stack[stackHead];
                stackHead--;
                num2 = stack[stackHead];
                stack[stackHead] = equal(num1,num2);
                printf("%d",stack[stackHead]);
                stackHead++;
                break;
            default:
                if(readCharAt(c,function) > 96){
                    int index = findIndexAlphabet(readCharAt(c,function));
                    stack[stackHead] = bitValueAt(rowNumber,numVariables-index-1);
                    stackHead++;
                    printf(" ");
                }else{
                    stack[stackHead] = readCharAt(c,function)-asciOffset;
                    stackHead++;
                    printf(" ");
                }
                break;
        }
    }
    printf(":   %d\n",stack[0]);
}
void printTableHeader(int numVariables,char* function){
    for(int c=0; c<numVariables;c++){
        printf("%c ",alphabet[c]);
    }
     printf(": %s : Result\n", function);
    int linelen = strlen(function) + 11 + (2*numVariables);
    for (int c=0;c<linelen;c++){
        printf("=");
    }
    printf("\n");
}

char readCharAt(int index, char* array){
    return array[index];
}

int findIndexAlphabet(char letter){
    int i = 0;
    while(i<27){
        if(alphabet[i]==letter) return i;
        i++;
    }
}