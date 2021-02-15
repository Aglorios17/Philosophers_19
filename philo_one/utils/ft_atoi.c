#include "../include/philo_one.h"

int    ft_atoi(const char *str)
{
    int                    i;
    int                    signe;
    unsigned long long    prev;
    unsigned long long    digit;

    i = 0;
    prev = 0;
    digit = 0;
    signe = 1;
    while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
        || str[i] == '\v' || str[i] == '\f')
        i++;
    if (str[i] == '-' || str[i] == '+')
        signe = (str[i++] == '-') ? -1 : 1;
    while (str[i] > 47 && str[i] < 58)
    {
        digit = digit * 10 + (str[i++] - '0');
        if (digit < prev || digit >= 9223372036854775807)
            return ((signe == -1) ? 0 : -1);
        prev = digit;
    }
    return (digit * signe);
}
