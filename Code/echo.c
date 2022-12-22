#include "headers.h"
void echo_(char *tokens[], int arg)
{
  for (int j = 1; j < arg; j++)
  {
    printf("%s ", tokens[j]);
  }
  printf("\n");
}