#define __FG
#ifdef __FG

void fg(char *tokens[], int backgrnd);
typedef struct node node;
struct node
{
  struct node *next;
  int proc_id;
  char *proc_name;
  int size;
};
extern int size_ll;
extern node *head, *tail;
extern double fg_time;
#endif