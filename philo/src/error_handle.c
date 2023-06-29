#include "../include/philo.h"

void	error_print()
{
	write(2, "Error occured\n", 15);
	exit(-1);
}

BOOL	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

BOOL philo_num_check(char *av)
{
    int philo_num;

    philo_num = (int) ft_atoi(av);
    if (philo_num <= 1 || philo_num > 200)
        return (FALSE);
    return (TRUE);
}

BOOL is_int(char *av)
{
    long long value;

    value = ft_atoi(av);
    if (value < 0 || value > INT_MAX)
        return (FALSE);
    return (TRUE);
}

BOOL argm_parse(int ac, char **av)
{
	int	i;

    i = 2;

    if (ac != 5 && ac != 6)
        return (FALSE);
    if (!philo_num_check(av[1]))
        return (FALSE);
    while (i < ac)
	{
        if (!(is_digit(av[i])))
            return (FALSE);
		if (!(is_int(av[i])))
            return (FALSE);
        i++;
	}
	return (TRUE);
}