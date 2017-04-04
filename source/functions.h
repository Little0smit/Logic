#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int bitValueAt(int number, int index);
int printTableRow(int rowNumber, int numVariables, char* function, char flag1);
int powInt(int x, int y);
void printTableHeader(int numVariables,char* function);
char* solveRow(int rowNumber,int numVariables,char* function);
char readCharAt(int index, char* array);
int findIndexAlphabet(char letter);

#endif /* FUNCTIONS_H */