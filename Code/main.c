#include "headers.h"
// sleep 5& sleep 2&sleep 3;sleep 5
void checkHostName(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}
void checkHostEntry(struct hostent *hostentry)
{
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}
char homedir[1000];
char currdir[1000];
char prevdir[1000];
char *history_arr[22];
pid_t process_id;
int e;
int history_pointer;
int no_of_and;
int count_comm;
int backgrnd = -1;
int size_ll;
node *head, *tail;
double fg_time;
char h[1000];
int min_(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}
int max_(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
char *directory_change()
{
    char *ans = (char *)calloc(1000, sizeof(char));
    // printf("\n%d\n", strncmp(currdir, homedir, strlen(homedir)));
    // printf("%s %s %ld %ld\n", currdir, homedir, strlen(homedir), strlen(currdir));
    if (strcmp(currdir, homedir) == 0)
    {
        ans[0] = '~';
    }
    // printf("%s\n", ans);
    else if (strlen(currdir) > strlen(homedir))
    {
        ans[0] = '~';
        ans[1] = '/';
        for (int j = strlen(homedir) + 1; j < strlen(currdir); j++)
        {
            ans[j - strlen(homedir) + 1] = currdir[j];
        }
        // printf("%s\n", ans);
    }
    else
    {
        strcpy(ans, currdir);
    }
    return ans;
}
void arr_directory(int n, char *x[])
{
    char *temp; // Pointer declaration
    int i, str;
    for (str = 0; str < n - 1; ++str)
    {
        for (i = str + 1; i < n; ++i)
        {
            if (strcmp(x[str], x[i]) > 0) // comparing the strings
            {
                temp = x[str]; // compared string being stored in temp
                x[str] = x[i];
                x[i] = temp;
            }
        }
    }
    return;
}

void history_save(int sig)
{
    strcpy(h, homedir);
    strcat(h, "/output.txt");
    FILE *f = fopen(h, "w+");
    for (int i = 0; i < 20; i++)
    {
        // printf("%s", history_arr[i]);
        fputs(history_arr[i], f); //
    }
    char pointer[10];
    sprintf(pointer, "%d", history_pointer - 1);
    fputs(pointer, f);
    sprintf(pointer, "%s", "\n");
    fputs(pointer, f);
    char pointer_[10];
    sprintf(pointer_, "%d", count_comm);
    fputs(pointer_, f);
    fclose(f);
    exit(0);
}
void c_handler(int sig)
{
    return;
}
void handler()
{
    node *prev = head;
    node *ptr = head;
    while (ptr != NULL)
    {
        // tmp->next = ptr;
        int status, if_normal = 0;
        if (waitpid(ptr->proc_id, &status, WNOHANG) != 0)
        {
            if (WIFEXITED(status) == 1)
                if_normal = 1;
            if (if_normal == 1)
                printf("\n%s with pid %d exited normally\n", ptr->proc_name, ptr->proc_id);
            else
                printf("\n%s with pid %d exited abnormally\n", ptr->proc_name, ptr->proc_id);
            if (prev == head && ptr == head)
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
        if (prev == ptr)
        {
            ptr = ptr->next;
            continue;
        }
        prev = prev->next;
        ptr = ptr->next;
    }
}
int main()
{
    signal(SIGCHLD, handler);
    signal(SIGINT, c_handler);
    for (int i = 0; i < 22; i++)
    {
        history_arr[i] = (char *)malloc(sizeof(char) * 300);
        strcpy(history_arr[i], " ");
    }
    char hostbuffer[256];
    struct hostent *host_entry;
    process_id = getpid();
    int hostname;
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);
    struct passwd *p;
    uid_t uid;
    getcwd(homedir, 1000);
    strcpy(prevdir, homedir);
    char h[1000];
    strcpy(h, homedir);
    strcat(h, "/output.txt");
    FILE *f = fopen(h, "r");
    char ch[400];
    for (int i = 0; i < 22; i++)
    {
        fgets(ch, 400, f);
        strcpy(history_arr[i], ch);
    }
    fclose(f);
    history_pointer = atoi(history_arr[20]) + 1;
    count_comm = atoi(history_arr[21]);
    // int counts = 0;

    while (1)
    {
        backgrnd = -1;
        if ((p = getpwuid(uid = getuid())) == NULL)
            perror("getpwuid() error");
        else
        {
            // printf("%d\n", history_pointer);
            // Printing the format on the terminal
            printf("\033[35m");
            printf("<%s", p->pw_name);
            printf("@");
            printf("%s:", hostbuffer);
            printf("\033[33m");
            getcwd(currdir, 1000);
            if (backgrnd == 0)
            {
                printf("took %.0lfs", fg_time);
                backgrnd = -1;
                fg_time = 0;
            }
            else
                printf("%s", directory_change());
            printf(">");
            // Ends here
            // the commands
            printf("\033[96m");
            size_t size = 1000;
            char *str = (char *)malloc(sizeof(char) * 1000);
            if (getline(&str, &size, stdin) == -1)
            {
                history_save(1);
            }
            char *semi_token = (char *)malloc(sizeof(char) * 1000);
            int commands = 0;
            const char semicolon[10] = ";";
            if (history_pointer >= 2)
            {
                if (strcmp(history_arr[history_pointer - 2], str) != 0)
                {
                    strcpy(history_arr[history_pointer - 1], str);
                    history_pointer++;
                    if (history_pointer == 21)
                    {
                        history_pointer = 1;
                    }
                }
                count_comm++;
            }
            else
            {
                strcpy(history_arr[history_pointer - 1], str);
                history_pointer++;
                if (history_pointer == 21)
                {
                    history_pointer = 1;
                }
                count_comm++;
            }
            semi_token = strtok(str, semicolon);
            if (semi_token == NULL)
            {
                continue;
            }
            // for (int i = 0; i < arg_temp; i++)
            // {
            char *string[1000];
            while (semi_token != NULL)
            {
                string[commands] = (char *)malloc(sizeof(char) * 1000);
                string[commands] = semi_token;
                commands++;
                semi_token = strtok(NULL, ";");
            }
            // for (int i = 0; i < commands; i++)
            //     printf("%s\n", string[i]);
            for (int i = 0; i < commands; i++)
            {
                no_of_and = 0;
                for (int j = 0; j < strlen(string[i]); j++)
                {
                    if (string[i][j] == '&')
                        no_of_and++;
                }
                char cwd[1000];
                char *and_token;
                and_token = strtok(string[i], "&");
                char *final_string[1000];
                int count = 0;
                while (and_token != NULL)
                {
                    final_string[count] = (char *)malloc(sizeof(char) * 1000);
                    final_string[count] = and_token;
                    count++;
                    and_token = strtok(NULL, "&");
                }
                if (count >= 2)
                {
                    backgrnd = 1;
                }
                for (e = 0; e < count; e++)
                {
                    char *token;
                    const char s[10] = " \t\r\n";
                    token = strtok(final_string[e], s);
                    if (token == NULL)
                        continue;
                    char *tokens[1000];
                    int arg = 0;
                    while (token != NULL)
                    {
                        tokens[arg] = (char *)malloc(sizeof(char) * 1000);
                        tokens[arg] = token;
                        arg++;
                        token = strtok(NULL, " \t\r\n");
                    }
                    execute(arg, tokens);
                }
            }
        }
    }
    return 0;
}
// printf("  pw_uid   : %d\n", (int) p->pw_uid);
// printf("  pw_gid   : %d\n", (int) p->pw_gid);
// printf("  pw_dir   : %s\n",       p->pw_dir);
// printf("%s\n", p->pw_shell);
// getcwd