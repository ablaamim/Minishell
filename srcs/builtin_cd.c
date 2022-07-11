/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:13:15 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 19:20:00 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*retrieve_cdpath(const char *dir)
{
	int			i;
	char		**paths;
	char		*cd_path;
	struct stat	buf;

	i = 0;
	paths = ft_split(get_env("CDPATH"), ':');
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		cd_path = ft_strjoin(paths[i], dir, "/");
		if (lstat(cd_path, &buf) == 0)
		{
			ft_free_arrays(paths);
			return (cd_path);
		}
		free(cd_path);
		i++;
	}
	ft_free_arrays(paths);
	return (NULL);
}

char	*ft_get_path(char **argv)
{
	char	*home;
	char	*cd_path;

	if (argv[1] == NULL)
	{
		home = get_env("HOME");
		if (home == NULL)
		{
			variadic_error_printer(STDERR_FILENO, \
					"minishell: %s: HOME not set\n", argv[0]);
			return (NULL);
		}
		return (home);
	}
	else
	{
		cd_path = retrieve_cdpath(argv[1]);
		if (cd_path == NULL)
			return (argv[1]);
		else
			return (cd_path);
	}
}

void	ft_update_pwd(char **argv)
{
	char		new[SIZE_8B];
	char		*pwd;

	if (getcwd(new, SIZE_8B) == NULL)
	{
		variadic_error_printer(STDERR_FILENO, \
				"pwd: error retrieving current directory: \
getcwd: cannot access parent directories: %s\n", strerror(errno));
		pwd = ft_strjoin(get_env("PWD"), argv[1], "");
		ft_set_env_var("PWD", pwd, 1);
		free(pwd);
	}
	else
		ft_set_env_var("PWD", new, 1);
}

int	ft_cd(int argc, char **argv)
{
	char		*path;
	char		old[SIZE_8B];

	if (argc > 2)
	{
		variadic_error_printer(STDERR_FILENO, \
				"minishell: cd: too many arguments");
		return (EXIT_FAILURE);
	}
	path = ft_get_path(argv);
	if (path == NULL)
		return (EXIT_FAILURE);
	if (getcwd(old, SIZE_8B) != NULL)
		ft_set_env_var("OLDPWD", old, 1);
	if (chdir(path) == -1)
	{
		variadic_error_printer(STDERR_FILENO,
			"minishell: %s: %s: No such file or directory\n", argv[0], argv[1],
			path);
		return (EXIT_FAILURE);
	}
	ft_update_pwd(argv);
	return (EXIT_SUCCESS);
}
