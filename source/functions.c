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
int printTableRow(int rowNumber, int numVariables, char* function, char flag1){
    if(flag1=='1'){
        char* solved ;//= calloc((strlen(function)+1),1);
        solved = solveRow(rowNumber, numVariables, function);
        if(solved[strlen(function)-1]=='1'){
            for(int c=numVariables-1;c>=0;c--){
                printf("%d ",bitValueAt(rowNumber,c));
            }
            printf(": ");
            printf("%s",solved);
            printf(" :   %c\n",solved[strlen(function)-1]);
        }
        return solved[strlen(function)-1]-asciOffset;
    } else {
        for(int c=numVariables-1;c>=0;c--){
            printf("%d ",bitValueAt(rowNumber,c));
        }
        char* solved = solveRow(rowNumber, numVariables, function);
        printf(": ");
        for(int i=0;i<strlen(solved)-1;i++){
            printf("%c",solved[i]);
        }
        printf(" :   %c\n",solved[strlen(function)]);
        int value = solved[strlen(function)-1]-asciOffset;
        free(solved);
        return value;
    }

}

char* solveRow(int rowNumber,int numVariables,char* function){
    int *stack = calloc(strlen(function),sizeof(int));
    int stackHead=0;
    int stringLength = strlen(function);
    char* response = calloc(stringLength+2,sizeof(char));
    for(int c=0;c<stringLength;c++){
        int num1=0, num2=0;
        switch(readCharAt(c,function)) {
            case '-':
                stackHead--;
                num1 = stack[stackHead];
                stack[stackHead] = negate(num1);
                response[c] = (char)stack[stackHead]+asciOffset;
                stackHead++;
                break;
            case '|':
                stackHead--;
                num1 = stack[stackHead];
                stackHead--;
                num2 = stack[stackHead];
                stack[stackHead] = or(num1,num2);
                response[c] = (char)stack[stackHead]+asciOffset;
                stackHead++;
                break;
            case '&':
                stackHead--;
                num1 = stack[stackHead];
                stackHead--;
                num2 = stack[stackHead];
                stack[stackHead] = and(num1,num2);
                response[c] = (char)stack[stackHead]+asciOffset;
                stackHead++;
                break;
            case '#':
                stackHead--;
                num1 = stack[stackHead];
                stackHead--;
                num2 = stack[stackHead];
                stack[stackHead] = exclusiveOr(num1,num2);
                response[c] = (char)stack[stackHead]+asciOffset;
                stackHead++;
                break;
            case '>':
                stackHead--;
                num2 = stack[stackHead];
                stackHead--;
                num1 = stack[stackHead];
                stack[stackHead] = implication(num1,num2);
                response[c] = (char)stack[stackHead]+asciOffset;
                stackHead++;
                break;
            case '=':
                stackHead--;
                num1 = stack[stackHead];
                stackHead--;
                num2 = stack[stackHead];
                stack[stackHead] = equal(num1,num2);
                response[c] = (char)stack[stackHead]+asciOffset;
                stackHead++;
                break;
            default:
                if(readCharAt(c,function) > 96){
                    int index = findIndexAlphabet(readCharAt(c,function));
                    stack[stackHead] = bitValueAt(rowNumber,numVariables-index-1);
                    stackHead++;
                    response[c] = ' ';
                }else{
                    stack[stackHead] = readCharAt(c,function)-asciOffset;
                    stackHead++;
                    response[c] = ' ';
                }
                break;
        }
    }
    stackHead--;
    response[stringLength] = stack[stackHead]+asciOffset;
    response[stringLength+1] = '\0';
    free(stack);
    return response;
}
void printTableHeader(int numVariables,char* function){
    for(int c=0; c<numVariables;c++){
        printf("%c ",alphabet[c]);
    }
     printf(": %s : Result\n", function);
    int linelen = (int) strlen(function) + 11 + (2*numVariables);
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