#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int bitValueAt(int number, int index);
void printTableRow(int rowNumber, int numVariables, char* function);
int powInt(int x, int y);
void printTableHeader(int numVariables,char* function);
void solveRow(int rowNumber,int numVariables,char* function);
char readCharAt(int index, char* array);
int findIndexAlphabet(char letter);

#endif /* FUNCTIONS_H */