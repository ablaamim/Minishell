/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:42:24 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 18:51:39 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_argument_is_dash_n(char *arg)
{
	if (*arg != '-')
		return (false);
	else
		++arg;
	while (*arg == 'n')
		++arg;
	if (*arg != '\0')
		return (false);
	return (true);
}

int	index_first_arg_to_print(char **argv, bool *has_dash_n_flag)
{
	int	i;

	i = 1;
	while (argv[i] != NULL && check_argument_is_dash_n(argv[i]) == true)
	{
		*has_dash_n_flag = true;
		++i;
	}
	return (i);
}

int	ft_echo_builtin(int argc, char **argv)
{
	bool			has_dash_n_flag;
	unsigned int	i;

	(void)argc;
	has_dash_n_flag = false;
	i = index_first_arg_to_print(argv, &has_dash_n_flag);
	while (argv[i] != NULL)
	{
		ft_putstr(argv[i]);
		++i;
		if (argv[i] != NULL)
			ft_putchar(' ');
	}
	if (has_dash_n_flag == false)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}
