/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:26:31 by mparasku          #+#    #+#             */
/*   Updated: 2023/06/28 14:30:54 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void free_linked_list(t_node *node)
{
    if (node->next != NULL)
    {
        free_linked_list(node->next);
    }
    free(node);
}

void free_rules(t_rules *rules)
{
    free(rules);
}

void free_data(t_data *data)
{
    free_linked_list(data->queue);
    free(data->philos);
	free(data);
}