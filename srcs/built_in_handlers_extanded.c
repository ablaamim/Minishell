/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_handlers_extanded.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:48:49 by gruz              #+#    #+#             */
/*   Updated: 2022/09/04 20:51:13 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_handle_unset(char **args)
{
    int i;
    int ret;

    i = 0x0;
    ret = EXIT_SUCCESS;
    while (args[i] != 0x0)
    {
        if (parse_unset(args[i]) == EXIT_FAILURE && ret == EXIT_SUCCESS)
            ret = EXIT_FAILURE;
        ft_unset_logic(args[i]);
        ++i;
    }
    return (ret);
}

int ft_handle_echo(char **args)
{
    int i;
    int j;
    int add_new_line;
    int k;

    i = 1;
    add_new_line = 1;
    j = ft_argv_len(args);
    while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
    {
        ft_echo_iterator(args, &k, i);
        if ((size_t)k < ft_strlen(args[i]))
            break;
        add_new_line = 0;
        i++;
    }
    ft_echo_print(args, i, j, add_new_line);
    return (EXIT_SUCCESS);
}