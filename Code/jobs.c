#include "headers.h"

void arr_directory_(int n, node *x[])
{
  node *temp; // Pointer declaration
  int i, str;
  for (str = 0; str < n - 1; ++str)
  {
    for (i = str + 1; i < n; ++i)
    {
      if (strcmp(x[str]->proc_name, x[i]->proc_name) > 0) // comparing the strings
      {
        temp = x[str]; // compared string being stored in temp
        x[str] = x[i];
        x[i] = temp;
      }
    }
  }
  return;
}
// void print()
// {
//   for (node *curr = head; curr != NULL; curr = curr->next)
//   {
//     printf("pid : %d", curr->proc_id);
//     printf(" pnm: %s\n", curr->proc_name);
//   }
// }
void jobs_(int arg, char *tokens[])
{
  // node *head, *tail;
  pid_t given_pid;
  int r_flag = 0, s_flag = 0;
  for (int i = 1; i < arg; i++)
  {
    if (strcmp(tokens[i], "-r") == 0)
      r_flag = 1;
    else if (strcmp(tokens[i], "-s") == 0)
      s_flag = 1;
  }
  node *arr[1000];
  int i = 0;
  for (node *curr = head; curr != NULL; curr = curr->next)
  {
    // arr[i] = (node *)malloc(sizeof(node));
    arr[i] = curr;
    i++;
    // printf("pname__ : %s", arr[i]->proc_name);
    // printf(" pnm: %s\n", curr->proc_name);
  }
  arr_directory_(i, arr);
  for (int j = 0; j < i; j++)
  {
    char path_stat[100];
    given_pid = process_id;
    sprintf(path_stat, "/proc/%d/stat", given_pid);
    FILE *f = fopen(path_stat, "r");
    char process_status[10];
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
    }
    if (r_flag == 0 && s_flag == 0)
    {
      if (strcmp(process_status, "S") == 0 || strcmp(process_status, "R") == 0)
        printf("[%d] Running %s [%d]\n", arr[j]->size, arr[j]->proc_name, arr[j]->proc_id);
      else
        printf("[%d] Stopped %s [%d]\n", arr[j]->size, arr[j]->proc_name, arr[j]->proc_id);
      // printf(" pnm: %s\n", curr->proc_name);
    }
    else if (r_flag == 0 && s_flag == 1)
    {
      if (strcmp(process_status, "S") == 0 || strcmp(process_status, "R") == 0)
        continue;
      else
        printf("[%d] Stopped %s [%d]\n", arr[j]->size, arr[j]->proc_name, arr[j]->proc_id);
    }
    else if (r_flag == 1 && s_flag == 0)
    {
      if (strcmp(process_status, "S") == 0 || strcmp(process_status, "R") == 0)
        printf("[%d] Running %s [%d]\n", arr[j]->size, arr[j]->proc_name, arr[j]->proc_id);
      else
        continue;
    }
  }
}
void sig_(int arg, char *tokens[])
{
  if (arg > 3 || arg < 3)
  {
    perror("sig");
    return;
  }
  int ongoing_job_number = atoi(tokens[1]);
  int signal_number = atoi(tokens[2]); // corresponding to the man page
  int proc_id = -1;
  for (node *curr = head; curr != NULL; curr = curr->next)
  {
    if (curr->size == ongoing_job_number)
    {
      proc_id = curr->proc_id;
      break;
    }
  }
  if (proc_id < 0)
  {
    perror("Error");
    return;
  }
  if (kill(proc_id, signal_number) < 0)
  {
    perror("Sig");
    return;
  }
}

void bg_to_run(int arg, char *tokens[])
{
  if (arg > 2)
  {
    perror("Error");
    return;
  }
  int ongoing_job_number = atoi(tokens[1]);
  int proc_id = -1;
  for (node *curr = head; curr != NULL; curr = curr->next)
  {
    if (curr->size == ongoing_job_number)
    {
      proc_id = curr->proc_id;
      break;
    }
  }
  if (proc_id < 0)
  {
    perror("Error");
    return;
  }
  if (kill(proc_id, SIGCONT) < 0)
  {
    perror("BG");
    return;
  }
}

void bg_to_fg(int arg, char *tokens[])
{
  backgrnd = 0;
  int signal_num = atoi(tokens[1]);
  int proc_id = -1;
  node *tmp;
  for (node *curr = head; curr != NULL; curr = curr->next)
  {
    if (curr->size == signal_num)
    {
      proc_id = curr->proc_id;
      tmp = curr;
      break;
    }
  }
  int status;
  setpgid(proc_id, getpgid(0));
  signal(SIGTTIN, SIG_IGN); // signal that causes Python to suspend in the following shell session when it attempts to read from stdin
  signal(SIGTTOU, SIG_IGN); // same thing for write
  tcsetpgrp(0, proc_id);
  if (kill(proc_id, SIGCONT) < 0)
    perror("Error");
  waitpid(proc_id, &status, WUNTRACED);
  tcsetpgrp(0, getpgid(0));

  // printf("bef_del-->\n");
  // print();
  signal(SIGTTIN, SIG_DFL);
  signal(SIGTTOU, SIG_DFL);

  if (proc_id < 0)
  {
    perror("Error");
    return;
  }
  // node *curr;
  // if (head != tail)
  // {
  //   for (curr = head; curr != tail; curr = curr->next)
  //     ;
  //   curr->next = NULL;
  //   curr = tail;
  //   // printf("tail -> %d\n", tail->proc_id);
  // }
  // else{

  // }
  node *prev = head;
  node *ptr = head;
  while (ptr != NULL)
  {
    // printf("head->%d ptr->%d tail->%d tmp->%d prev->%d\n", head->proc_id, ptr->proc_id, tail->proc_id, tmp->proc_id, prev->proc_id);
    if (ptr->proc_id == proc_id)
    {
      printf("heelo\n");
      if (ptr->proc_id == tail->proc_id)
      {
        prev->next = NULL;
        tail = prev;
        ptr = tail;
      }
      else if (prev->proc_id == head->proc_id && ptr->proc_id == head->proc_id)
      {
        prev->next = ptr->next;
        head = ptr->next;
        // free(ptr);
        ptr = head;
      }
      else
      {
        prev->next = ptr->next;
        node *temp = ptr->next;
        // free(ptr);
        ptr = temp;
      }
      size_ll--;
      continue;
    }
    if (ptr->proc_id == prev->proc_id)
    {
      ptr = ptr->next;
      continue;
    }
    prev = prev->next;
    ptr = ptr->next;
  }
  size_ll++;
  // printf("after_del-->\n");
  // print();
  // continue;
  // end pe delte ni hora

  return;
}