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


