/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:18:36 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/12 16:15:23 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_data(t_data *data)
{
	if (data->philos != NULL)
		free(data->philos);
	if (data->rules != NULL)
		free(data->rules);
	free(data);
}

t_data	*ft_error_exit(char *str, t_data *data, int flag)
{
	printf("%s\n", str);
	if (flag == 1)
	{
		free_data(data);
		return (NULL);
	}
	else
		return (NULL);
}
