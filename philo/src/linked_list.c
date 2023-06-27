# include "../include/linked_list.h"

void free_linked_list(t_node *node)
{
    if (node->next != NULL)
    {
        free_linked_list(node->next);
    }
    free(node);
}