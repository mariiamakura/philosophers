/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:18:57 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/13 14:34:46 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define BOOL int
# define TRUE 1
# define FALSE 0
# define TEAKEN_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>


typedef struct s_rules
{
	int	philo_num;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	req_eat;
}	t_rules;

typedef struct s_philo
{
	struct s_data	*data;
	pid_t			pid;
	int				id;
	int				meal_times;
	int				eating;
	long			time_die;
	t_rules			*rules;
}	t_philo;

typedef struct s_data
{
	t_rules			*rules;
	int				is_dead;
	int				finished;
	long			start_time;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*message;
	sem_t			*death;
	sem_t			*stop;
}	t_data;

//error_handle.c
int			error_print(void);
BOOL		argm_parse(int ac, char **av);
BOOL		is_digit(char *str);
BOOL		philo_num_check(char *av);
BOOL		is_int(char *av);

//utils.c
long long	ft_atoi(const char *str);
long		ft_get_time(void);
int			ft_strcmp(char *s1, char *s2);
void		message(char *str, t_philo *philo);
void		ft_destroy_all(t_data *data);

//init.c
t_data		*init(t_data *data, char **av, int ac);
t_data		*init_rules(char **av, int ac, t_data *data);
t_data		*alloc_structs(t_data *data);
t_data		*init_philo(t_data *data);

//sem_init.c
t_data *sem_create(t_data *data);
void ft_process_create(t_data *data);
void	p_routine(t_philo *philo);
void *supervisor_bonus(void *data_ptr);

//freeing.c
t_data	*ft_error_exit(char *str, t_data *data, int flag);
void	free_data(t_data *data);

#endif