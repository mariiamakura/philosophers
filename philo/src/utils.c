#include "../include/philo.h"

long long	ft_atoi(const char *str)
{
    int			neg;
    long long	number;
    int			i;

    neg = 1;
    i = 0;
    number = 0;
    if (!str)
        return (0);
    while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
        i++;
    if (str[i] == '-')
        neg = -1;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        number = (number * 10) + (str[i] - '0');
        i++;
    }
    return (number * neg);
}

void revome_node(t_node **head, int data)
{
	t_node *current;
	t_node *prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (current->data == data)
		{
			if (prev == NULL)
				*head = current->next;
			else 
				prev->next = current->next;
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void add_back_note(t_node **head, int data)
{
	t_node *new;
	t_node *current;

	current = *head;
	new = (t_node *)malloc(sizeof(t_node));
	new->data = data;
	new->next = NULL;
	if (new == NULL)
		error_print();
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}
