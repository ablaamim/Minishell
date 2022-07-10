/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:02:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 19:06:54 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(int argc, char **argv)
{
	char	path[SIZE_8B];

	(void)(argc && argv);
	if (getcwd(path, SIZE_8B) == NULL)
		variadic_error_printer(STDERR_FILENO, \
				"pwd: error retrieving current directory: getcwd: cannot \
				access parent directories: %s", strerror(errno));
	else
		ft_putstr(path);
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}
