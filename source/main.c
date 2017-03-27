#include "functions.h"

int main(int argc, char* argv[]) {
  char numVariables  = *argv[1];
  char* function = argv[2];
  int rows = powInt(2,(numVariables-'0'));
  printTableHeader(numVariables-'0', function);
  for(int c=0;c<rows;c++){
    printTableRow(c,(numVariables-'0'),function);
  }
}
