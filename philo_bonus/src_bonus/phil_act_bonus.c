/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_act_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:54:57 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/14 14:16:36 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	message(TEAKEN_FORK, philo);
	sem_wait(philo->data->forks);
	message(TEAKEN_FORK, philo);
}

void	put_forks_bonus(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}
