#ifndef LOGIC_PARSER_H
#define LOGIC_PARSER_H

typedef enum {OR,AND,IMPLICATION,EXCLUSIVEOR,EQUAL,NEGATE,LB,RB,NUMBER} ETokenType;
typedef struct {ETokenType type; char value; int precedence;} TokenStruct;
char* ParseInput(char* input);
TokenStruct TokeniseInput(char token_value);
#endif //LOGIC_PARSER_H
