#include "headers.h"
// pid...process_name..next..size
double fg_time;
node *init()
{
  node *n = (node *)malloc(sizeof(node));
  // n->pid = 0;
  n->next = NULL;
  // n->process_name = "";
  n->size = 0;
  return n;
}
node *head, *tail = NULL;
void print()
{
  for (node *curr = head; curr != NULL; curr = curr->next)
  {
    printf("pid : %d", curr->proc_id);
    printf(" pnm: %s\n", curr->proc_name);
  }
}
void fg(char **tokens, int backgrnd)
{
  int process_id = fork();

  if (process_id < 0)
  {
    perror("Error");
    return;
  }
  if (process_id == 0)
  {
    // printf("hellooo\n");
    setpgid(0, 0);

    if (execvp(tokens[0], tokens) < 0)
    {
      perror("Error");
      return;
    }
    exit(0);
  }
  else
  {
    if (backgrnd == 1) // background process
    {
      // printf("Heleo\n");
      printf("[%d] %d\n", size_ll + 1, process_id);
      // return process_id;
      // print();
      node *new = init();
      new->proc_id = process_id;
      new->proc_name = (char *)malloc(sizeof(char) * (strlen(tokens[0]) + 1));
      strcpy(new->proc_name, tokens[0]);
      if (head == NULL)
      {
        head = new;
        tail = new;
      }
      else
      {
        tail->next = new;
        tail = new;
        // printf("okok:%d\n", tail->proc_id);
      }
      size_ll++;
      new->size = size_ll;
      // size_ll--;
      // printf("okok-->\n");
      // print();
      size_ll = 0;
      for (node *curr = head; curr != NULL; curr = curr->next)
      {
        size_ll++;
      }
      // printf("name %s size %d\n", new->proc_name, size_ll);
    }
    else
    {
      int status;
      // time_t begin hote...time_t end hote...time end - begin
      time_t begin = time(NULL);
      signal(SIGTTIN, SIG_IGN); // signal that causes Python to suspend in the following shell session when it attempts to read from stdin
      signal(SIGTTOU, SIG_IGN); // same thing for write

      tcsetpgrp(0, process_id);
      waitpid(process_id, &status, WUNTRACED);
      if(WIFSTOPPED(status))
      {
        node *new = init();
        new->proc_id = process_id;
        new->proc_name = (char *)malloc(sizeof(char) * (strlen(tokens[0]) + 1));
        strcpy(new->proc_name, tokens[0]);
        if (head == NULL)
        {
          head = new;
          tail = new;
        }
        else
        {
          tail->next = new;
          tail = new;
          // printf("okok:%d\n", tail->proc_id);
        }
        size_ll++;
        new->size = size_ll;
        printf("[%d] %s with pid %d pushed to the background\n",new->size,new->proc_name,new->proc_id);
      }
      tcsetpgrp(0, getpgid(0));

      signal(SIGTTIN, SIG_DFL);
      signal(SIGTTOU, SIG_DFL);
      time_t end = time(NULL);
      fg_time += end - begin;
    }
  }
}