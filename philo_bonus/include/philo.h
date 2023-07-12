/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:18:57 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/05 17:20:04 by mparasku         ###   ########.fr       */
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
	pthread_t		t1;
	int				id;
	int				meal_times;
	int				status;
	int				eating;
	long			time_die;
	t_rules			*rules;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	t_rules			*rules;
	int				is_dead;
	int				finished;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
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

//init.c
t_data		*init(t_data *data, char **av, int ac);
t_data		*init_rules(char **av, int ac, t_data *data);
t_data		*alloc_structs(t_data *data);
t_data		*init_forks(t_data *data);
t_data		*init_philo(t_data *data);

//freeing.c
t_data		*ft_error_exit(char *str, t_data *data, int flag);
void		destroy_mutex(t_data *data);
void		free_data(t_data *data);

//threads.c
BOOL		thread_init(t_data *data);
void		*supervisor(void *data_ptr);
void		*p_routine(void *philo_ptr);

//philo_act.c
void		eat(t_philo *philo);
void		take_forks(t_philo *philo);
void		put_forks(t_philo *philo);
void		message(char *str, t_philo *philo);

#endif