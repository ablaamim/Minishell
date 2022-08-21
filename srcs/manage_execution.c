/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 22:58:37 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/21 13:07:21 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_an_executable(char *bin_path)
{
	if (access(bin_path, X_OK) == -1)
		return (false);
	return (true);
}

int	is_a_directory(char *bin_path)
{
	struct stat	data;

	if (stat(bin_path, &data) == -1)
		return (-1);
	if (S_ISDIR(data.st_mode) == 1)
		return (1);
	return (0);
}

int	manage_error(char *binary_path, char *cmd, char *error, int exit_val)
{
	garbage_free((void **) &binary_path);
	variadic_error_printer(2, "minishell : %s : %s\n", cmd, error);
	return (exit_val);
}

int	manage_execution(char *binary_path, char *cmd)
{
	int	ret;

	if (binary_path == 0x0)
	{
		if (get_env("PATH") == 0x0)
			return (manage_error(0x0, cmd, "No such file or directory", 127));
		else
			return (manage_error(0x0, cmd, "Command not found", 127));
	}
	ret = is_a_directory(binary_path);
	if (ret == 1)
		return (manage_error(binary_path, cmd, strerror(errno), 126));
	else if (ret == -1)
		return (manage_error(binary_path, cmd, strerror(errno), 127));
	if (is_an_executable(binary_path) == false)
		return (manage_error(binary_path, cmd, strerror(errno), 126));
	return (EXIT_SUCCESS);
}
