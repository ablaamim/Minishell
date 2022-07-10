/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:05:57 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 19:08:08 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtins_executor(int argc, char **argv, t_io_streams_file saver)
{
	int					i;
	t_builtin const	builtin[] = {
		//{.name = "cd", .func = &cd},
		{.name = "echo", .func = &ft_echo_builtin},
		//{.name = "env", .func = &ft_env},
		{.name = "exit", .func = &ft_exit_builtin},
		{.name = "pwd", .func = &ft_pwd},
		//{.name = "export", .func = &export},
		//{.name = "unset", .func = &unset},
		{.name = NULL}
	};

	i = 0;
	(void) argc;
	if (ft_strcmp(argv[0], "exit") == 0x0)
		ft_close_fd(saver);
	while (builtin[i].name != NULL && ft_strcmp(argv[0], builtin[i].name))
		i++;
	if (builtin[i].name == NULL)
		return (EXIT_COMMAND_NOT_FOUND);
	exit_value_set(builtin[i].func(argc, argv));
	return (EXIT_SUCCESS);
}
