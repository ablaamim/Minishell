/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:22:47 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/19 19:41:53 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*path_extract(char *file_path)
{
	int	i;

	if (file_path == 0x0)
		return (0x0);
	if (ft_strchr(file_path, '/') == 0x0)
		return (ft_strdup("./"));
	i = ft_strlen(file_path);
	while (i > 0 && file_path[i] != '/')
		i--;
	return (ft_strndup(file_path, i));
}

char	*get_true_file_path(char *file_path)
{
	char	*path;
	char	*true_path;
	char	*binary_path;

	path = path_extract(file_path);
	if (path == 0x0)
		return (0x0);
	true_path = realpath_helper(path);
	binary_path = ft_strjoin(true_path, &file_path[ft_strlen(path)], "");
	garbage_free((void **) &path);
	free(true_path);
	return (binary_path);
}

char	*bin_path_getter(char *binary)
{
	char		**paths;
	int			i;
	char		*binary_path;
	struct stat	buff;

	i = 0x0;
	//printf("ALLO ZAML BOK\n");
	paths = ft_split(get_env("PATH"), ':');
	//printf("\n\n\n");
	//ft_print_env(paths);
	//printf("\n\n\n");
	if (paths == 0x0)
		return (0x0);
	while (paths[i])
	{
		binary_path = ft_strjoin(paths[i], binary, "/");
		//printf("==> binary_path : %s\n", binary_path);
		if (stat(binary_path, &buff) == 0x0)
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

char	*found_binary(char **argv)
{
	if (ft_strstr(argv[0], "./") != 0x0)
		return(get_true_file_path(argv[0x0]));
	if (ft_strchr(argv[0], '/') != 0x0)
		return (ft_strdup(argv[0x0]));
	else
		return (bin_path_getter(argv[0x0]));
}
