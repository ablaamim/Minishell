/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:46:01 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/17 15:11:16 by ablaamim         ###   ########.fr       */
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
	paths = ft_split(get_env("PATH"), ':');
	if (paths == 0x0)
		return (0x0);
	ft_print_env(paths);
	while (paths[i])
	{
		binary_path = ft_strjoin(paths[i], binary, "/");
		printf("%s\n", binary_path);
		return (binary_path);
		garbage_free((void **) &binary_path);
		i++;
	}
	//printf("%s\n", binary_path);
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

	ft_print_simple_cmd(argv);
	env = get_bash_env();
	binary_path = verify_bin_path(argv);
	//ret = execution_manager(binary_path, argv[0]);
	//if (ret != EXIT_SUCCESS)
	//	return (ret);
	if (execve(binary_path, argv, *env) == -1)
		printf("ERROR MANAGING SHOULD BE DONE.\n");
	garbage_free((void **)&binary_path);
	return (EXIT_SUCCESS);
}
