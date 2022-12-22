#include "headers.h"

void history_(int history_pointer, int count_comm)
{
  // printf("-->%d\n", count_comm);
  // printf("->%d\n", history_pointer);
  int tmp;
  if (count_comm >= 20)
  {
    for (int i = 10 + history_pointer -1; i < 20; i++)
    {
      // if (history_arr[i] != " ")
      printf("%s", history_arr[i]);
    }
  }
  if (history_pointer - 1 < 10)
    tmp = 0;
  else
  {
    tmp = history_pointer - 1 - 10;
  }
  for (int i = tmp; i < history_pointer - 1; i++)
  {
    printf("%s", history_arr[i]);
  }
  return;
}