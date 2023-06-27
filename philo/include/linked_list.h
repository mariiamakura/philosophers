# include <stdlib.h>

typedef struct s_node
{
    int data;
    struct s_node *next;
} t_node;

void free_linked_list(t_node *node);
