// #define _execute
// #ifdef _execute
void execute(int arg, char *tokens[]);
extern char homedir[1000];
extern char currdir[1000];
extern char prevdir[1000];
extern char *history_arr[22];
extern int history_pointer;
extern int count_comm;
extern int backgrnd;
extern void history_save(int sig);
extern int e;
extern int no_of_and;
extern int org_output_fd;
extern int org_input_fd;
// #endif