#include "../includes/minishell.h"

int is_white_space(char c)
{
    char *white_spaces;

    white_spaces = " \t\n\v\f\r";
    while (*white_spaces)
    {
        if (*white_spaces == c)
            return (1);
        white_spaces++;
    }
    return (0);
}

int calculate_return(int ne)
{
    if (ne > 0)
        return (-1);
    else
        return (0);
}

int ft_atoi_(const char *string)
{
    size_t i;
    int ne;
    size_t to_return;

    i = 0;
    ne = 1;
    to_return = 0;
    while (is_white_space(string[i]) == 1)
        i++;
    if (string[i] == '\0')
        return (0);
    if (string[i] == '-' || string[i] == '+')
    {
        if (string[i] == '-')
            ne = -1;
        i++;
    }
    while (ft_isdigit(string[i]) != 0)
    {
        if (to_return > 9223372036854775807)
            return (0);
        to_return = (string[i] - '0') + (10 * to_return);
        i++;
    }
    return (to_return * ne);
}