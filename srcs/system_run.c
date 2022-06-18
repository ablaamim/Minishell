/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:46:01 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/18 18:05:01 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Return the path of binary, Null if not found.
 * [THESE FUNCTIONS ARE BUGGY].
*/

char	*retrieve_bin_path(const char	*binary)
{
	char	**paths;
	int		i;
	char	*binary_path;

	i = 0x0;
	//printf("PATH=%s\n", get_env("PATH"));
	paths = ft_split(get_env("PATH"), ':');
	if (paths == 0x0)
		return (0x0);
	while (paths[i])
	{
		printf("===================| DATA DEBUG |=======================\n\n");
		printf("====> PATHS %s %d\n\n", paths[i], i);
		binary_path = ft_strjoin(paths[i], binary, "/");
		//printf("==> BINARY PATH : %s\n", binary_path);
		return (binary_path);
		garbage_free((void **) &binary_path);
		i++;
	}
	ft_free_arrays(paths);
	return (0x0);
}

/*
 *
*/

char	*verify_bin_path(char **argv)
{
	if (ft_strchr(argv[0], '/') != 0x0)
		return (ft_strdup(argv[0]));
	else
		return (retrieve_bin_path(argv[0]));
}

int	error_manager(char	*binary_path, char	*cmd, char	*error, int	exit_val)
{
	garbage_free((void **) &binary_path);
	write(2, "ERROR : \n", sizeof("ERROR : \n"));
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
	//ret_val = ft_is_dir(binary_path); // GOTTA VERIFY THIS LATER
	printf("ALLO ???\n\n");
	if (ret_val == -1)
		return (error_manager(binary_path, cmd, strerror(errno), \
					EXIT_COMMAND_NOT_FOUND));
	if (ft_is_executable(binary_path) == false)
	{
		printf("\n\n==> ACCESS FAILED\n\n");
		return (error_manager(binary_path, cmd, strerror(errno), \
					EXIT_COMMAND_NOT_FOUND));
	}
	return (EXIT_SUCCESS);
}

/*
 * Check path validity and execute cmd in child process.
*/

int	system_run(char	**argv)
{
	char	*binary_path;
	t_env	*env;
	int		ret;

	printf("-----------------------------------------------------------\n\n");
	ft_print_simple_cmd(argv);
	printf("-----------------------------------------------------------\n\n");
	env = get_bash_env();
	binary_path = verify_bin_path(argv);
	//ret = execution_manager(binary_path, argv[0]);
	//if (ret != EXIT_SUCCESS)
	//	return (ret);
	/*
	 * I HAVE TO FIX THIS SHIT !
	*/
	printf("%s\n", binary_path);
	printf("====> BINARY PATH CORRUPTED DUH...\n\n");
	/*
	 * CASE CLOSED.
	*/
	//ft_print_env(*env);
	printf("%s\n", argv[0]);
	if (execve(binary_path, argv, *env) == -1)
	{
		printf("EXECVE FAILED : ERROR MANAGING SHOULD BE DONE!!!!!\n\n");
		// TO DO : 
		return (error_manager(binary_path, argv[0], strerror(errno), \
					EXIT_COMMAND_NOT_FOUND));
	}
	garbage_free((void **)&binary_path);
	return (EXIT_SUCCESS);
}
