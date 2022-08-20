#include "../includes/minishell.h"

int ft_isdigit(int v)
{
    if (v >= 48 && v <= 57)
        return (1);
    else
        return (0);
}