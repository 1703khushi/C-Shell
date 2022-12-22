#include "headers.h"

int d_flag = 0, f_flag = 0;
struct stat file;
char to_find[1000];
char given_dir[1000];
char *final[1000];
char tmp[1000];
void func(char *directory)
{
  DIR *dir;
  struct dirent *entry;
  // printf("%s\n", directory);
  if ((dir = opendir(directory)) == NULL)
  {
    // printf("hello\n");
    perror("error");
  }
  else
  {
    char p_curr_wd[1000];
    getcwd(p_curr_wd, 1000);
    // ..
    while ((entry = readdir(dir)) != NULL)
    {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        continue;
      // if (strcmp(entry->d_name, to_find) == 0)
      // {
      //   char temp_[1000];
      //   strcpy(temp_, directory);
      //   strcat(temp_, "/");
      //   strcat(temp_, entry->d_name);
      //   if (stat(temp_, &file) == 0 && S_ISREG(file.st_mode) != 0 && f_flag == 1)
      //   {
      //     break;
      //   }
      // }

      char temp[1000];
      strcpy(temp, directory);
      strcat(temp, "/");
      strcat(temp, entry->d_name);
      // printf("%s\n", temp);
      if (stat(temp, &file) == 0 && S_ISDIR(file.st_mode) != 0)
      {
        chdir(temp);
        char curr_wd[1000];
        getcwd(curr_wd, 1000);
        func(curr_wd);
        chdir(p_curr_wd);
      }
      // else
      if (strcmp(to_find, entry->d_name) != 0)
      {
        if (strcmp(to_find, "") != 0)
        {
          continue;
        }
      }
      if (f_flag == 1 && d_flag == 0)
      {
        if (stat(temp, &file) == 0 && S_ISDIR(file.st_mode) != 0)
          continue;
        // if (stat(temp, &file) == 0 && S_ISDIR(file.st_mode) != 0)
        //   continue;
      }
      if (f_flag == 0 && d_flag == 1)
      {
        // printf("--%s\n", temp);

        if (stat(temp, &file) == 0 && S_ISREG(file.st_mode) != 0)
          continue;
      }
      if (strcmp(to_find, temp) == 0)
      {
        if (f_flag == 1 && stat(temp, &file) == 0 && S_ISREG(file.st_mode) != 0 && f_flag == 1)
          continue;
        if (d_flag == 1 && stat(temp, &file) == 0 && S_ISDIR(file.st_mode) != 0 && f_flag == 1)
          continue;
      }
      // {
      // getcwd(p_curr_wd, 1000);
      char path[1000];
      strcpy(path, ".");
      strcat(path, &temp[strlen(currdir)]);
      printf("%s\n", path);
      // }
    }
  }
}
void discover_(int arg, char *tokens[])
{
  d_flag = 0, f_flag = 0;
  int flag = 0;
  strcpy(to_find, "");
  strcpy(given_dir, currdir);
  // printf("%s\n", given_dir);
  for (int i = 1; i < arg; i++)
  {
    if (strcmp(tokens[i], "-d") == 0)
    {
      d_flag = 1;
      continue;
    }
    if (strcmp(tokens[i], "-f") == 0)
    {
      f_flag = 1;
      continue;
    }
    if (tokens[i][0] == '"')
    {
      // printf("hello\n");
      // char s[2] = "\";
      char *token = strtok(tokens[i], "\"");
      strcpy(to_find, token);
      flag = 1;
    }
    else if (stat(tokens[i], &file) == 0 && S_ISDIR(file.st_mode) != 0)
    {
      if (tokens[i][0] == '.')
      {
        strcat(given_dir, &tokens[i][1]);
      }
      else
      {
        strcat(given_dir, "/");
        strcat(given_dir, tokens[i]);
      }
    }
    else
    {
      // printf("hello\n");

      perror("Error");
      return;
    }
  }
  if (flag == 0)
  {
    char tmp_path[1000] = "";
    if (strcmp(to_find, "") == 0)
    {
      // printf("2222");
      strcpy(tmp_path, "./");
      strcat(tmp_path, &given_dir[strlen(currdir) + 1]);
      printf("%s\n", tmp_path);
    }
  }
  // printf("%d %d %s %s\n", d_flag, f_flag, given_dir, to_find);
  func(given_dir);
}

// totla in ls
// fg bg bugs
// discover ka dir_1/dir_3 wala part