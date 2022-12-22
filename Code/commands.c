#include "headers.h"
int org_input_fd, org_output_fd;
void commands_(int arg, char *tokens[])
{
  char cwd[1000];
  char pwd[5] = "pwd";
  char cd[5] = "cd";
  char echo[5] = "echo";
  char history[10] = "history";
  char exit[5] = "exit";
  char ls[5] = "ls";
  char pinfo[10] = "pinfo";
  char discover[20] = "discover";
  char jobs[5] = "jobs";
  char sig[5] = "sig";
  char bgtofg[10] = "fg";
  char bgtorun[10] = "bg";
  if (strcmp(tokens[0], echo) == 0)
  {
    echo_(tokens, arg);
  }
  else if (strcmp(tokens[0], pwd) == 0)
  {
    printf("%s\n", getcwd(cwd, sizeof(cwd)));
  }
  else if (strcmp(tokens[0], cd) == 0)
  {
    cd_(tokens, arg);
  }
  else if (strcmp(tokens[0], history) == 0)
  {
    history_(history_pointer, count_comm);
  }
  else if (strcmp(tokens[0], jobs) == 0)
  {
    jobs_(arg, tokens);
  }
  else if (strcmp(tokens[0], exit) == 0)
  {
    history_save(0);
    return;
  }
  else if (strcmp(tokens[0], ls) == 0)
  {
    ls_(arg, tokens);
  }
  else if (strcmp(tokens[0], pinfo) == 0)
  {
    pinfo_(arg, tokens);
  }
  else if (strcmp(tokens[0], discover) == 0)
  {
    discover_(arg, tokens);
  }
  else if (strcmp(tokens[0], sig) == 0)
  {
    sig_(arg, tokens);
  }
  else if (strcmp(tokens[0], bgtofg) == 0)
  {
    bg_to_fg(arg, tokens);
  }
  else if (strcmp(tokens[0], bgtorun) == 0)
  {
    bg_to_run(arg, tokens);
  }
  else
  {
    tokens[arg] = NULL;
    // printf("&-> %d\n", no_of_and);
    if (e < no_of_and)
    {
      // for (int i = 0; i < arg; i++)
      //     printf("%s\n", tokens[i]);
      // printf("okokoko\n");
      backgrnd = 1;
      fg(tokens, 1);
    }
    else
    {
      backgrnd = 0;
      fg(tokens, 0);
    }
  }
  dup2(org_input_fd, STDIN_FILENO);
  dup2(org_output_fd, STDOUT_FILENO);
}