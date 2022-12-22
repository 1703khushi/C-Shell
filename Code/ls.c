#include "headers.h"
DIR *dir;
struct dirent *entry;
struct stat file;
struct passwd *pwuser;
struct group *grpnam;
unsigned int sum;
char *arr[1000];
int a_count = 0, l_count = 0, d_count = 1;

void print_as_flags(int i, int arg)
{
  // if (l_count == 1)
  // {
  //   sum = 0;
  //   for (int j = 0; j < i; j++)
  //   {
  //     if (stat(arr[j], &file) == 0)
  //       sum += file.st_blocks;
  //     // printf("%ld\n", file.st_blocks);
  //   }
  // }
  arr_directory(i, arr);
  if (a_count == 0 && l_count == 0)
  {
    for (int j = 0; j < i; j++)
    {
      if (arr[j][0] != '.')
      {
        if (stat(arr[j], &file) == 0 && S_ISDIR(file.st_mode))
          printf("\033[94m"); // green
        else if (stat(arr[j], &file) == 0 && file.st_mode & S_IXUSR)
          printf("\033[92m"); // blue
        else if (stat(arr[j], &file) == 0 && S_ISREG(file.st_mode))
          printf("\033[97m"); // white
        printf("%s\n", arr[j]);
        printf("\033[0m");
      }
    }
  }
  else if (a_count == 1 && l_count == 0)
  {
    for (int j = 0; j < i; j++)
    {
      if (stat(arr[j], &file) == 0 && S_ISDIR(file.st_mode))
      {
        printf("\033[94m"); // green
        printf("%s\n", arr[j]);
        printf("\033[0m");
      }
      else if (stat(arr[j], &file) == 0 && file.st_mode & S_IXUSR)
      {
        printf("\033[92m"); // blue
        printf("%s\n", arr[j]);
        printf("\033[0m");
      }
      else if (stat(arr[j], &file) == 0 && S_ISREG(file.st_mode))
      {
        printf("\033[97m"); // white
        printf("%s\n", arr[j]);
        printf("\033[0m");
      }
    }
  }
  else if (a_count == 1 && l_count == 1)
  {
    // if (l_count == 1)
    // {
    sum = 0;
    for (int j = 0; j < i; j++)
    {
      // if (arr[j][0] == '.')
      //   continue;
      if (stat(arr[j], &file) == 0)
        sum += file.st_blocks;
      // printf("%ld\n", file.st_blocks);
    }

    printf("\033[32m");
    printf("total %d\n", sum / 2);
    // }
    for (int j = 0; j < i; j++)
    {
      printf("\033[90m");
      // printf("Hello\n");
      if (stat(arr[j], &file) == 0 && S_ISDIR(file.st_mode))
        printf("d");
      else
        printf("-");
      if (stat(arr[j], &file) == 0 && file.st_mode & S_IRUSR)
        printf("r");
      else
        printf("-");
      if (stat(arr[j], &file) == 0 && file.st_mode & S_IWUSR)
        printf("w");
      else
        printf("-");
      if (stat(arr[j], &file) == 0 && file.st_mode & S_IXUSR)
        printf("x");
      else
        printf("-");
      if (stat(arr[j], &file) == 0 && file.st_mode & S_IRGRP)
        printf("r");
      else
        printf("-");
      if (stat(arr[j], &file) == 0 && file.st_mode & S_IWGRP)
        printf("w");
      else
        printf("-");
      if (stat(arr[j], &file) == 0 && file.st_mode & S_IXGRP)
        printf("x");
      else
        printf("-");
      if (stat(arr[j], &file) == 0 && file.st_mode & S_IROTH)
        printf("r");
      else
        printf("-");
      if (stat(arr[j], &file) == 0 && file.st_mode & S_IWOTH)
        printf("w");
      else
        printf("-");
      if (stat(arr[j], &file) == 0 && file.st_mode & S_IXOTH)
        printf("x");
      else
        printf("-");
      printf("\033[34m");
      printf("  %ld", file.st_nlink);
      if (NULL == (pwuser = getpwuid(file.st_uid)))
      {
        perror("getpwuid()");
      }
      if (NULL == (grpnam = getgrgid(file.st_gid)))
      {
        perror("getgrgid()");
      }
      printf("\033[32m");
      printf(" %s", pwuser->pw_name);
      printf("\033[97m");
      printf(" %s", grpnam->gr_name);
      struct tm tm;
      printf("\033[31m");
      printf("%6.ld ", file.st_size); /* you may use %lld */
      localtime_r(&file.st_ctim.tv_sec, &tm);
      printf("\033[93m");

      if (tm.tm_mon + 1 == 1)
        printf("Jan");
      else if (tm.tm_mon + 1 == 2)
        printf("Feb");
      else if (tm.tm_mon + 1 == 3)
        printf("Mar");
      else if (tm.tm_mon + 1 == 4)
        printf("Apr");
      else if (tm.tm_mon + 1 == 5)
        printf("May");
      else if (tm.tm_mon + 1 == 6)
        printf("Jun");
      else if (tm.tm_mon + 1 == 7)
        printf("Jul");
      else if (tm.tm_mon + 1 == 8)
        printf("Aug");
      else if (tm.tm_mon + 1 == 9)
        printf("Sep");
      else if (tm.tm_mon + 1 == 10)
        printf("Oct");
      else if (tm.tm_mon + 1 == 11)
        printf("Nov");
      else if (tm.tm_mon + 1 == 12)
        printf("Dec");
      printf(" %2.d", tm.tm_mday);

      printf(" %02i:%02i", tm.tm_hour, tm.tm_min);

      if (stat(arr[j], &file) == 0 && S_ISDIR(file.st_mode))
      {
        printf("\033[94m"); // green
        printf(" %s\n", arr[j]);
        printf("\033[0m");
      }
      else if (stat(arr[j], &file) == 0 && file.st_mode & S_IXUSR)
      {
        printf("\033[92m"); // blue
        printf(" %s\n", arr[j]);
        printf("\033[0m");
      }
      else if (stat(arr[j], &file) == 0 && S_ISREG(file.st_mode))
      {
        printf("\033[97m"); // white
        printf(" %s\n", arr[j]);
        printf("\033[0m");
      }
    }
  }
  else if (a_count == 0 && l_count == 1)
  {
    sum = 0;
    for (int j = 0; j < i; j++)
    {
      if (arr[j][0] == '.')
        continue;
      if (stat(arr[j], &file) == 0)
        sum += file.st_blocks;
      // printf("%ld\n", file.st_blocks);
    }

    printf("\033[32m");
    printf("total %d\n", sum / 2);

    for (int j = 0; j < i; j++)
    {
      if (arr[j][0] != '.')
      {
        printf("\033[90m");
        // printf("Hello\n");
        if (stat(arr[j], &file) == 0 && S_ISDIR(file.st_mode))
          printf("d");
        else
          printf("-");
        if (stat(arr[j], &file) == 0 && file.st_mode & S_IRUSR)
          printf("r");
        else
          printf("-");
        if (stat(arr[j], &file) == 0 && file.st_mode & S_IWUSR)
          printf("w");
        else
          printf("-");
        if (stat(arr[j], &file) == 0 && file.st_mode & S_IXUSR)
          printf("x");
        else
          printf("-");
        if (stat(arr[j], &file) == 0 && file.st_mode & S_IRGRP)
          printf("r");
        else
          printf("-");
        if (stat(arr[j], &file) == 0 && file.st_mode & S_IWGRP)
          printf("w");
        else
          printf("-");
        if (stat(arr[j], &file) == 0 && file.st_mode & S_IXGRP)
          printf("x");
        else
          printf("-");
        if (stat(arr[j], &file) == 0 && file.st_mode & S_IROTH)
          printf("r");
        else
          printf("-");
        if (stat(arr[j], &file) == 0 && file.st_mode & S_IWOTH)
          printf("w");
        else
          printf("-");
        if (stat(arr[j], &file) == 0 && file.st_mode & S_IXOTH)
          printf("x");
        else
          printf("-");
        printf("\033[34m");
        printf("  %ld", file.st_nlink);
        if (NULL == (pwuser = getpwuid(file.st_uid)))
        {
          perror("getpwuid()");
        }
        if (NULL == (grpnam = getgrgid(file.st_gid)))
        {
          perror("getgrgid()");
        }
        printf("\033[32m");
        printf(" %s", pwuser->pw_name);
        printf("\033[97m");
        printf(" %s", grpnam->gr_name);
        struct tm tm;
        printf("\033[31m");
        printf("%7.ld ", file.st_size); /* you may use %lld */
        localtime_r(&file.st_ctim.tv_sec, &tm);
        printf("\033[93m");

        if (tm.tm_mon + 1 == 1)
          printf("Jan");
        else if (tm.tm_mon + 1 == 2)
          printf("Feb");
        else if (tm.tm_mon + 1 == 3)
          printf("Mar");
        else if (tm.tm_mon + 1 == 4)
          printf("Apr");
        else if (tm.tm_mon + 1 == 5)
          printf("May");
        else if (tm.tm_mon + 1 == 6)
          printf("Jun");
        else if (tm.tm_mon + 1 == 7)
          printf("Jul");
        else if (tm.tm_mon + 1 == 8)
          printf("Aug");
        else if (tm.tm_mon + 1 == 9)
          printf("Sep");
        else if (tm.tm_mon + 1 == 10)
          printf("Oct");
        else if (tm.tm_mon + 1 == 11)
          printf("Nov");
        else if (tm.tm_mon + 1 == 12)
          printf("Dec");
        printf(" %2.d", tm.tm_mday);

        printf(" %02i:%02i", tm.tm_hour, tm.tm_min);

        if (stat(arr[j], &file) == 0 && S_ISDIR(file.st_mode))
        {
          printf("\033[94m"); // green
          printf(" %s\n", arr[j]);
          printf("\033[0m");
        }
        else if (stat(arr[j], &file) == 0 && file.st_mode & S_IXUSR)
        {
          printf("\033[92m"); // blue
          printf(" %s\n", arr[j]);
          printf("\033[0m");
        }
        else if (stat(arr[j], &file) == 0 && S_ISREG(file.st_mode))
        {
          printf("\033[97m"); // white
          printf(" %s\n", arr[j]);
          printf("\033[0m");
        }
      }
    }
  }
}
//
void ls_(int arg, char *tokens[])
{
  // printf("%s\n", getcwd(currdir, 1000));
  a_count = 0, l_count = 0, d_count = 1;
  char *tmparr[100];
  char tmpdir[100];
  a_count = 0, l_count = 0, d_count = 0;
  for (int i = 1; i < arg; i++)
  {
    if (strcmp(tokens[i], "-a") == 0)
      a_count++;
    else if (strcmp(tokens[i], "-l") == 0)
      l_count++;
    else if (strcmp(tokens[i], "-al") == 0 || strcmp(tokens[i], "-la") == 0)
    {
      a_count++;
      l_count++;
    }
    else
    {
      tmparr[d_count] = (char *)malloc(sizeof(char) * 300);
      strcpy(tmparr[d_count], tokens[i]);
      // printf("%s\n", tmparr[d_count]);
      d_count++;
    }
  }
  // int flag = 0;
  if (d_count == 0)
  {
    tmparr[0] = (char *)malloc(100 * sizeof(char));
    strcpy(tmparr[0], ".");
    // flag = 1;
    d_count++;
  }
  for (int i = 0; i < d_count; i++)
  {
    // if (l_count == 1)
    // {
    //   sum = 0;
    //   for (int j = 0; j < d_count; j++)
    //   {
    //     sum += file.st_blocks;
    //     printf("%ld\n", file.st_blocks);
    //   }
    // }
    char tmr[1000];
    strcpy(tmr, tmparr[i]);
    char *abc = (char *)malloc(300 * sizeof(char));
    if (tmr[0] == '~')
    {
      char path[400];
      strcpy(path, homedir);
      strcpy(tmr, strcat(path, &tmr[1]));
      // printf("----------------%s\n",tmr);
    }
    struct stat st;
    if (stat(tmr, &st) == -1)
    {
      perror("Error: ");
      return;
    }
    if (S_ISREG(st.st_mode) == 0)
    {
      if (chdir(tmr) == -1)
      {
        perror("Error: ");
        return;
      }
      // char current[400];
      getcwd(abc, 400);
    }
    else
    {
      int k = 1;
      arr[0] = (char *)malloc(100 * sizeof(char));
      strcpy(arr[0], tmparr[0]);
      printf("%s:\n", tmr);
      print_as_flags(k, arg);
      if (d_count != 1)
        printf("\n");
      continue;
    }

    // printf("-->%s\n", abc);
    // printf("%s\n",abc);
    if ((dir = opendir(abc)) == NULL)
      perror("Error");
    else
    {
      int i = 0;
      while ((entry = readdir(dir)) != NULL)
      {
        arr[i] = (char *)malloc(sizeof(char) * 1000);
        strcpy(arr[i], entry->d_name);
        // printf("000%s\n", arr[i]);
        i++;
      }
      printf("\033[97m");
      if (d_count > 1)
        printf("%s:\n", tmr);

      print_as_flags(i, arg);
    }
    chdir(currdir);
    closedir(dir);
    if (i != d_count - 1)
      printf("\n");
  }
}