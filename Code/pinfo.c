#include "headers.h"

void pinfo_(int arg, char *tokens[])
{
  pid_t given_pid;
  char process_status[10];
  char process_memory[100];
  char process_path[1000];
  if (arg > 2)
  {
    printf("Too many arguments\n");
    return;
  }
  else if (arg == 2)
    given_pid = atoi(tokens[1]);
  else
    given_pid = process_id;

  char path_stat[100], path_exe[100];

  sprintf(path_stat, "/proc/%d/stat", given_pid);
  sprintf(path_exe, "/proc/%d/exe", given_pid);

  FILE *f = fopen(path_stat, "r");

  if (!f)
  {
    perror(path_stat);
    return;
  }
  else
  {
    char proc[1000];
    char *process[100];
    fgets(proc, 1000, f);
    char *token;
    token = strtok(proc, " ");
    int c = 0;
    while (token != NULL)
    {
      process[c] = (char *)malloc(sizeof(char) * 1000);
      process[c] = token;
      c++;
      token = strtok(NULL, " ");
    }

    strcpy(process_status, process[2]);
    strcpy(process_memory, process[22]);
    int process_group = atoi(process[4]);
    int term_group = atoi(process[7]);

    if (process_group == term_group)
    {
      process_status[1] = '+';
      process_status[2] = 0;
    }
    else
    {
      process_status[1] = 0;
    }
    fclose(f);
  }
  char buffer[1000] = "";
  if (readlink(path_exe, buffer, 1000) == -1)
  {
    perror(path_exe);
    return;
  }
  else
  {
    int path_len = strlen(buffer);
    int home_len = strlen(homedir);
    if (path_len >= home_len)
    {
      process_path[0] = '~';
      strcpy(&process_path[1], &buffer[home_len]);
    }
    else
    {
      strcpy(process_path, buffer);
    }
  }
  printf("pid : %d\n", process_id);
  printf("process Status : %s\n", process_status);
  printf("memory : %s\n", process_memory);
  printf("executable Path : %s\n", process_path);
}