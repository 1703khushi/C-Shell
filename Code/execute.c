#include "headers.h"

void execute(int arg, char *tokens[])
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
  // char input_file[1000] = "";
  // char output_file[1000] = "";
  // int no_of_and;
  int append_flag = 0;
  int arg_temp = arg;
  char *tmp_arr[1000];
  int k = 0;
  // printf("%d\n", arg);
  int org_output_fd;
  int org_input_fd;
  int pipe_count = 0;
  for (int i = 0; i < arg_temp; i++)
  {
    if (strcmp(tokens[i], "|") == 0)
      pipe_count++;
  }

  int j = 0;
  char *tmp_arr_[1000];
  int i;
  // int flag = 0;
  for (int u = 0; u <= pipe_count; u++)
  {
    k = 0;
    int fd_input;
    int out_flag = 0, in_flag = 0, append_flag = 0, pipe_input = 0;

    for (i = j; i < arg_temp; i++)
    {
      if (strcmp(tokens[i], ">") == 0)
      {
        org_output_fd = dup(STDOUT_FILENO);
        int fd_output;
        fd_output = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_output < 0)
        {
          perror("Error");
          return;
        }
        if (dup2(fd_output, STDOUT_FILENO) < 0)
        {
          perror("Cannot duplicate the file descriptor");
          return;
        }
        out_flag = 1;
        i++;
        arg--;
        arg--;
      }
      else if (strcmp(tokens[i], ">>") == 0)
      {
        org_output_fd = dup(STDOUT_FILENO);
        int fd_append;
        fd_append = open(tokens[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd_append < 0)
        {
          perror("Error");
          return;
        }
        if (dup2(fd_append, STDOUT_FILENO) < 0)
        {
          perror("Cannot duplicate the file descriptor");
          return;
        }
        i++;
        append_flag = 1;
        arg--;
        arg--;
      }
      else if (strcmp(tokens[i], "<") == 0)
      {
        org_input_fd = dup(STDIN_FILENO);
        fd_input = open(tokens[i + 1], O_RDONLY);
        if (fd_input < 0)
        {
          perror("Error");
          return;
        }
        if (dup2(fd_input, STDIN_FILENO) < 0)
        {
          perror("Cannot duplicate the file descriptor");
          return;
        }
        i++;
        in_flag = 1;
        arg--;
        arg--;
      }
      else if (strcmp(tokens[i], "|") == 0)
      {
        // printf("hello\n");
        int tube[2];
        if (pipe(tube) < 0)
        {
          perror("pipe: ");
          continue;
        }

        // if (out_flag == 0)
        // {
          // printf("%dhello\n", k);
          org_output_fd = dup(STDOUT_FILENO);
          dup2(tube[1], STDOUT_FILENO);
          // tube[1] = dup(STDOUT_FILENO);
          // printf("ookokoko\n");
        // }

        // for (int p = 0; p < k; p++)
        //   printf("%s\n", tmp_arr_[p]);
        commands_(k, tmp_arr_);
        close(tube[1]);
        dup2(org_output_fd, STDOUT_FILENO);
        // if (in_flag == 0)
        // {
        //   dup2(org_input_fd, STDIN_FILENO);
        //   in_flag = 0;
        //   close(fd_input);
        // }
        // else
        // {
        if (pipe_input == 1)
        {
          dup2(org_input_fd, STDIN_FILENO);
          pipe_input = 0;
        }
        org_input_fd = dup(STDIN_FILENO);
        dup2(tube[0], STDIN_FILENO);
        pipe_input = 1;

        // printf("ojadk\n");
        // }
        // flag = 1;
        // dup2(org_input_fd, STDIN_FILENO);
        // dup2(org_output_fd, STDOUT_FILENO);
        break;
      }
      else
      {
        tmp_arr_[1000];
        tmp_arr_[k] = (char *)malloc(sizeof(char) * 1000);
        strcpy(tmp_arr_[k], tokens[i]);
        // printf("->%d %s\n", k, tmp_arr[k]);
        k++;
      }
    }
    // printf("%d\n", i);
    j = i + 1;

    // // printf("ok reacked\n");
    // for (int g = 0; g < k; g++)
    // {
    //   printf("->%s\n", tmp_arr_[g]);
    // }
    // printf("--> %d\n", k);
    // // }
  }
  commands_(k, tmp_arr_);
  dup2(org_input_fd, STDIN_FILENO);
  dup2(org_output_fd, STDOUT_FILENO);

  return;
}