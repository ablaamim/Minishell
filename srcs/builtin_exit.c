/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:51:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 18:57:59 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isnumber(char *s)
{
	int	i;

	i = 0;
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

int	ft_get_status(int argc, char **argv)
{
	int	status;

	status = *retrieve_exit_status();
	if (argc >= 2)
	{
		if (ft_isnumber(argv[1]) == 0)
		{
			variadic_error_printer(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required\n", argv[1]);
			status = 2;
		}
		else if (argc > 2)
		{
			variadic_error_printer(STDERR_FILENO, \
					"minishell: exit: too many arguments\n");
			return (EXIT_FAILURE);
		}
		else
			status = ft_atoi(argv[1]);
	}
	return (status);
}

int	ft_exit_builtin(int argc, char **argv)
{
	int		status;
	bool	piped;

	piped = *ft_pipe_getter();
	if (piped == false)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	status = ft_get_status(argc, argv);
	if (piped == false)
		shell_exit(status, NULL);
	return (status);
}
