#include "../include/philo.h"

void	error_print()
{
	write(2, "Error occured\n", 15);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	argm_parse(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!(is_digit(av[i])))
			return (0);
		i++;
	}
	return (1);
}