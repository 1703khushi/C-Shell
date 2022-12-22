#include "headers.h"

void cd_(char *tokens[], int arg)
{
  char t[100];
  // printf("--%s\n", currdir);
  if (arg <= 2)
  {
    if (arg == 1 || strcmp(tokens[1], "~") == 0)
    {
      chdir(homedir);
      strcpy(prevdir, currdir);
      getcwd(currdir, 1000);
    }
    else if (strcmp(tokens[1], "..") == 0)
    {
      // printf("hellllo\n");
      chdir("..");
      strcpy(prevdir, currdir);
      getcwd(currdir, 1000);
    }
    else if (strcmp(tokens[1], "-") == 0)
    {
      // printf("hellooo\n");
      chdir(prevdir);
      strcpy(prevdir, currdir);
      getcwd(currdir, 1000); //
      printf("%s\n", currdir);
    }
    else if (strcmp(tokens[1], ".") == 0)
    {
      // printf("%s %s\n", prevdir, currdir);
      strcpy(prevdir, currdir);
      getcwd(currdir, 1000);
      return;
    }
    else
    {
      char temp[1000];
      strcpy(temp, currdir);
      strcat(temp, "/");
      strcat(temp, tokens[1]);
      if (chdir(temp) == 0)
      {
        strcpy(prevdir, currdir);
        strcat(currdir, "/");
        // printf("%s\n", tokens[1]);
        //
        strcat(currdir, tokens[1]);
        chdir(currdir);
      }
      else
      {
        perror("Error");
      }
    }
  }
  else
  {
    // for (int i = 0; i < arg; i++)
    //   printf("%s", tokens[i]);
    printf("too many arguments\n");
  }
}