// #define _JOBS
// #ifndef _JOBS
void jobs_(int arg, char *tokens[]);
extern void arr_directory(int n, char *x[]);
extern void print();
void sig_(int arg, char *tokens[]);
void bg_to_run(int arg, char *tokens[]);
void bg_to_fg(int arg, char *tokens[]);
extern node *head, *tail;
extern pid_t process_id;
extern int backgrnd;
// #endif