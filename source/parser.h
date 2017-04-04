#ifndef LOGIC_PARSER_H
#define LOGIC_PARSER_H

typedef enum {OR,AND,IMPLICATION,EXCLUSIVEOR,EQUAL,NEGATE,LB,RB,NUMBER} ETokenType;
typedef struct {ETokenType type; char value; int precedence;} TokenStruct;
typedef struct {TokenStruct* data; int head; int tail; int topPrecedence;} StackQueue;
char* ParseInput(char* input);
TokenStruct TokeniseInput(char token_value);
StackQueue* InitStackQueue(int maxSize);
void PushQueueStack(TokenStruct CurrentToken,StackQueue* SQ, char sq);
TokenStruct PopStack(StackQueue* Stack);
TokenStruct PopQueue(StackQueue* Queue);
#endif //LOGIC_PARSER_H
