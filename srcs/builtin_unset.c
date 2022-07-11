/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:09:21 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/11 08:00:03 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_identifier(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	{
		variadic_error_printer(STDERR_FILENO,
			"minishell: unset: `%s': not a valid identifier\n", arg);
		return (EXIT_FAILURE);
	}
	while (arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			variadic_error_printer(STDERR_FILENO,
				"minishell: unset: `%s': not a valid identifier\n", arg);
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_unset(int argc, char **argv)
{
	int	i;
	int	ret;

	(void)argc;
	i = 0;
	ret = EXIT_SUCCESS;
	while (argv[i] != NULL)
	{
		if (check_identifier(argv[i]) == EXIT_FAILURE && ret == EXIT_SUCCESS)
			ret = EXIT_FAILURE;
		ft_unsetenv(argv[i]);
		++i;
	}
	return (ret);
}

