#include "parser.h"
#include "functions.h"
#include <stdlib.h>
#include <memory.h>

//Takes a string of algebraic notation and parses it into RPN
char* ParseInput(char* input){
    int string_length = (int)strlen(input);
    StackQueue* Stack = InitStackQueue(string_length);
    StackQueue* Queue = InitStackQueue(string_length);
    TokenStruct CurrentToken;
    char s = 'S';
    char q = 'Q';
    //Loop through each character of input string and convert into a Token.
    for(int c=0;c<string_length;c++){
        char current_char = readCharAt(c,input);
        if(current_char!=32){
            CurrentToken = TokeniseInput(current_char);
            //Depending on what token is, add to queue or stack, or pop from stack.
            if(CurrentToken.type == NUMBER) {
                PushQueueStack(CurrentToken, Queue,q);
            } else if(CurrentToken.type == LB) {
                PushQueueStack(CurrentToken, Stack,s);
            } else if(CurrentToken.type == RB) {
                //Pop from stack until a LB is found
                CurrentToken = PopStack(Stack);
                while (CurrentToken.type != LB) {
                    PushQueueStack(CurrentToken, Queue,q);
                    CurrentToken = PopStack(Stack);
                }
            }else if(CurrentToken.precedence < Stack->topPrecedence){
                //Add a straight to the queue
                PushQueueStack(CurrentToken, Stack,s);
            } else {
                while (CurrentToken.precedence > Stack->topPrecedence && Stack->topPrecedence>-1){
                    PushQueueStack(PopStack(Stack), Queue,q);
                }
                PushQueueStack(CurrentToken, Stack,s);
            }
        }

    }
    while(Stack->head>Stack->tail){
        PushQueueStack(PopStack(Stack), Queue,q);
    }
    int c = 0;
    char* output = calloc(sizeof(char),string_length);
    while(Queue->tail<Queue->head){
        output[c++] = PopQueue(Queue).value;
    }
    output[c]='\0';
    return output;
}

//Takes a character and returns a Token struct representing that character
TokenStruct TokeniseInput(char token_value){
    TokenStruct Token;
    //TODO add precedence rules so brackets not needed
    int token_precedence;
    ETokenType token_type;
    Token.value = token_value;
    switch(token_value) {
        case '-':
            token_type = NEGATE;
            token_precedence = 1;
            break;
        case '|':
            token_type = OR;
            token_precedence = 2;
            break;
        case '&':
            token_type = AND;
            token_precedence = 3;
            break;
        case '#':
            token_type = EXCLUSIVEOR;
            token_precedence = 4;
            break;
        case '>':
            token_type = IMPLICATION;
            token_precedence = 5;
            break;
        case '=':
            token_type = EQUAL;
            token_precedence = 6;
            break;
        case '(':
            token_type = LB;
            token_precedence = 7;
            break;
        case ')':
            token_type = RB;
            token_precedence = 7;
            break;
        default:
            token_type = NUMBER;
            token_precedence = 0;
            break;
    }
    Token.type = token_type;
    Token.precedence = token_precedence;
    return Token;
}

StackQueue* InitStackQueue(int maxSize){
    StackQueue* SQ = calloc(1,sizeof(StackQueue));
    TokenStruct* data = calloc(maxSize, sizeof(TokenStruct));
    SQ->data = data;
    SQ->head = 0;
    SQ->tail = 0;
    SQ->topPrecedence = -1;
    return SQ;
}

void PushQueueStack(TokenStruct CurrentToken,StackQueue* SQ, char sq){
    SQ->data[SQ->head].precedence = CurrentToken.precedence;
    SQ->data[SQ->head].value = CurrentToken.value;
    SQ->data[SQ->head].type = CurrentToken.type;
    SQ->head++;
    if(CurrentToken.precedence == 7 ){
        SQ->topPrecedence = -1;
    }else{
        SQ->topPrecedence = CurrentToken.precedence;
    }
}

TokenStruct PopStack(StackQueue* Stack){
    TokenStruct Token;
    Stack->head--;
    Token.type = Stack->data[Stack->head].type;
    Token.value = Stack->data[Stack->head].value;
    Token.precedence = Stack->data[Stack->head].precedence;
    if(Stack->data[Stack->head-1].precedence == 7 ){
        Stack->topPrecedence = -1;
    }else{
        Stack->topPrecedence = Stack->data[Stack->head-1].precedence;
    }
    if(Stack->head==Stack->tail){
        Stack->topPrecedence=-1;
    }
    return Token;
}

TokenStruct PopQueue(StackQueue* Queue){
    TokenStruct Token;
    Token.type = Queue->data[Queue->tail].type;
    Token.value = Queue->data[Queue->tail].value;
    Token.precedence = Queue->data[Queue->tail].precedence;
    Queue->tail++;
    return Token;
}