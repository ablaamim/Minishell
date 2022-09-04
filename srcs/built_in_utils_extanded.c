/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils_extanded.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:49:58 by gruz              #+#    #+#             */
/*   Updated: 2022/09/04 21:26:02 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_echo_iterator(char **args, int *k, int i)
{
    *k = 1;
    while (args[i][*k] == 'n')
        (*k)++;
}

void ft_echo_print(char **args, int i, int j, int add_new_line)
{
    while (args[i])
    {
        printf("%s", args[i++]);
        if (i < j)
            printf(" ");
    }
    if (add_new_line)
        printf("\n");
}

int ft_handle_built_ins(char **args)
{
	int exit_stat;

	exit_stat = *retrieve_exit_status();
	if (!ft_strcmp(args[0], "export"))
		exit_stat = ft_handle_export(args);
	else if (!ft_strcmp(args[0], "unset"))
		exit_stat = ft_handle_unset(args);
	else if (!ft_strcmp(args[0], "env"))
		exit_stat = ft_handle_env(args);
	else if (!ft_strcmp(args[0], "echo"))
		exit_stat = ft_handle_echo(args);
	else if (!ft_strcmp(args[0], "pwd"))
		exit_stat = ft_handle_pwd();
	else if (!ft_strcmp(args[0], "cd"))
		exit_stat = ft_handle_cd(args);
	else if (!ft_strcmp(args[0], "exit"))
	{
		exit_stat = ft_handle_exit(args);
		exit(exit_stat);
	}
	exit_value_set(exit_stat);
	return (exit_stat);
}

int	ft_isnumber(char *s)
{
	int	i;

	i = 0x0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	export_len_name(char *argument)
{
	int	len;

	len = 0x0;
	while (argument[len] != '+' && argument[len] != '=' && argument[len] != '\0')
		++len;
	return (len);
}
