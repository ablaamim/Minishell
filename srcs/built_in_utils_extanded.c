/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils_extanded.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:49:58 by gruz              #+#    #+#             */
/*   Updated: 2022/09/06 20:08:03 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_iterator(char **args, int *k, int i)
{
	*k = 1;
	while (args[i][*k] == 'n')
		(*k)++;
}

void	ft_echo_print(t_node *node, int i, int j, int add_new_line)
{
	char	**args;

	args = node->content.simple_cmd.argv;
	while (args[i])
	{
		variadic_error_printer(node->content.simple_cmd.fd_out,
			"%s", args[i++]);
		if (i < j)
			variadic_error_printer(node->content.simple_cmd.fd_out, " ");
	}
	if (add_new_line)
		variadic_error_printer(node->content.simple_cmd.fd_out, "\n");
}

int	ft_handle_built_ins(char **args, t_node *node)
{
	int	exit_stat;
	int	err;

	exit_stat = *retrieve_exit_status();
	err = 0;
	if (!ft_strcmp(args[0], "export"))
		exit_stat = ft_handle_export(args, node);
	else if (!ft_strcmp(args[0], "unset"))
		exit_stat = ft_handle_unset(args);
	else if (!ft_strcmp(args[0], "env"))
		exit_stat = ft_handle_env(args, node);
	else if (!ft_strcmp(args[0], "echo"))
		exit_stat = ft_handle_echo(args, node);
	else if (!ft_strcmp(args[0], "pwd"))
		exit_stat = ft_handle_pwd(node);
	else if (!ft_strcmp(args[0], "cd"))
		exit_stat = ft_handle_cd(args);
	else if (!ft_strcmp(args[0], "exit"))
	{
		exit_stat = ft_handle_exit(args, node, &err);
		if (err != 1)
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
	while (argument[len] != '+' && argument[len]
		!= '=' && argument[len] != '\0')
		++len;
	return (len);
}
