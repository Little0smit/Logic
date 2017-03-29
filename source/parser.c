#include "parser.h"

//Takes a string of algebraic notation and parses it into RPN
char* ParseInput(char* input){
    int string_length = strlen(input);
    TokenStruct* token_stack = calloc(string_length, sizeof(TokenStruct));
    int token_stack_head = 0;
    TokenStruct* token_queue = calloc(string_length, sizeof(TokenStruct));
    int token_queue_tail = 0;
    for(int c=0;c<string_length;c++){
        TokeniseInput(readCharAt(c,input));
        printf("Woop");
    }
}

//Takes a character and returns a Token struct representing that character
TokenStruct TokeniseInput(char token_value){
    TokenStruct Token;
    //TODO add precedence rules so brackets not needed
    //int token_precedence;
    ETokenType token_type;
    strcpy(Token.value, token_value);
    switch(token_value) {
        case '-':
            token_type = NEGATE;
            break;
        case '|':
            token_type = OR;
            break;
        case '&':
            token_type = AND;
            break;
        case '#':
            token_type = EXCLUSIVEOR;
            break;
        case '>':
            token_type = IMPLICATION;
            break;
        case '=':
            token_type = EQUAL;
            break;
        case '(':
            token_type = LB;
            break;
        case ')':
            token_type = RB;
            break;
        default:
            token_type = NUMBER;
            break;
    }
    Token.type = token_type;
    return Token;
}