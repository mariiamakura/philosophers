#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

//error_handle.c
void	error_print();
int		argm_parse(int ac, char **av);
int		is_digit(char *str);


#endif