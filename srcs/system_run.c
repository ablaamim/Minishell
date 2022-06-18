/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:46:01 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/18 15:52:39 by ablaamim         ###   ########.fr       */
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
	 * ENABLE TO PRINT ENV VALUES !!
	*/
	//ft_print_env(*env);
	if (execve(binary_path, argv, *env) == -1)
	{
		printf("EXECVE FAILED : ERROR MANAGING SHOULD BE DONE!!!!!\n\n");
		// TO DO : 
		/*
		return (ft_error_manager(binary_path, argv[0], strerror(errno), \
					EXEC_ERROR));
		*/
	}
	garbage_free((void **)&binary_path);
	return (EXIT_SUCCESS);
}
