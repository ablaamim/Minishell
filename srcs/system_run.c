/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:46:01 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 17:40:03 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Return the path of binary, Null if not found.
 * [THESE FUNCTIONS ARE BUGGY].
 * [CASSE CLOSED]
*/

char	*retrieve_bin_path(const char	*binary)
{
	char		**paths;
	int			i;
	char		*binary_path;
	struct stat	buff;

	i = 0x0;
	paths = ft_split(get_env("PATH"), ':');
	if (paths == 0x0)
		return (0x0);
	while (paths[i])
	{
		printf("===================| DATA DEBUG |=======================\n\n");

		printf("=====> All paths : \n\n");
		int	param = 0x0;
		while(paths[param])
		{
			printf("%s\n", paths[param]);
			param++;
		}
		binary_path = ft_strjoin(paths[i], binary, "/");
		if (stat(binary_path, &buff) == 0)
		{
			ft_free_arrays(paths);
			return (binary_path);
		}
		free(binary_path);
		i++;
	}
	ft_free_arrays(paths);
	return (0x0);
}

char	*verify_bin_path(char **argv)
{
	if (ft_strchr(argv[0], "./" != 0x0))
		return (get_true_filepath(argv[0]));
	else if (ft_strchr(argv[0], '/') != 0x0)
		return (ft_strdup(argv[0]));
	else
		return (retrieve_bin_path(argv[0]));
}

int	error_manager(char *binary_path, char *cmd, char *error, int exit_val)
{
	free(binary_path);
	variadic_error_printer(2, "Minishell : %s %s\n", cmd, error);
	return (exit_val);
}

int	ft_exec_manager(char	*binary_path, char	*cmd)
{
	int	ret_val;

	if (binary_path == 0x0)
	{
		if (get_env("PATH") == 0x0)
			return (error_manager(0x0, cmd, "No such file or directory\n", \
						EXIT_COMMAND_NOT_FOUND));
		else
			return (error_manager(0x0, cmd, "Command not found\n", \
						EXIT_COMMAND_NOT_FOUND));
	}
	ret_val = ft_is_directory(binary_path);
	if (ret_val == 1)
		return (error_manager(binary_path, cmd, "Is a directory",
				EXEC_EXIT_ERROR));
	else if (ret_val == -1)
		return (error_manager(binary_path, cmd, strerror(errno),
				EXIT_COMMAND_NOT_FOUND));
	if (ft_is_executable(binary_path) == false)
		return (error_manager(binary_path, cmd, strerror(errno), \
					EXIT_COMMAND_NOT_FOUND));
	return (EXIT_SUCCESS);
}

/*
 * Check path validity and execute cmd in child process if path of binary
 * is valid.
 * else ==> print error on stderr.
*/

int	system_run(char	**argv)
{
	char	*binary_path;
	t_env	*env;
	int		ret;

	ft_print_simple_cmd(argv);
	env = get_bash_env();
	binary_path = verify_bin_path(argv);
	ret = ft_exec_manager(binary_path, argv[0]);
	if (ret != EXIT_SUCCESS)
		return (ret);
	printf("\n\n====> BINARY_PATH SENT TO EXECVE : %s\n\n", binary_path);
	if (execve(binary_path, argv, *env) == -1)
		return (error_manager(binary_path, argv[0], strerror(errno), \
					EXEC_EXIT_ERROR));
	free(binary_path);
	return (EXIT_SUCCESS);
}
