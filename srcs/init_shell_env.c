/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:18:54 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/04 14:51:34 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * These function will allow host bash cache cloning in order to get a copy 
 * of env.
 * -> bonus functionalities :
 * SHELL VAR IS EXPENDED.
 * SHLVL ALSO.
*/

char	*path_extracter(char const *filepath)
{
	int	i;
	
	if (filepath == 0x0)
		return (0x0);
	if (ft_strchr(filepath, '/') == 0x0)
		return (ft_strdup("./"));
	i = ft_strlen(filepath);
	while (i > 0 && filepath[i] != '/')
		i--;
	return (ft_strndup(filepath, i));
}

char	*realpath_helper(char const *path)
{
	char	*real_path;
	char	pwd[SIZE_10B];

	if (ft_strchr(path, '/') == 0x0 && chdir("./") == -1)
		return (0x0);
	if (chdir(path) == -1)
		return (0x0);
	real_path = getcwd(0x0, 0x0);
	if (real_path == 0x0)
		shell_exit(EXIT_FAILURE, "getcwd(): failed to get pwd.");
	getcwd(pwd, SIZE_10B);
	if (chdir(pwd) == -1)
	{
		free(real_path);
		shell_exit(EXIT_FAILURE, "chdir(): failed to reset pwd.");
	}
	return (real_path);
}

char	*get_true_filepath(char const *filepath)
{
	char	*real_path;
	char	*path;
	char	*binary_path;

	path = path_extracter(filepath);
	if (path == 0x0)
		return (0x0);
	real_path = realpath_helper(path);
	if (real_path == 0x0)
		return (0x0);
	binary_path = ft_strjoin(real_path, &filepath[ft_strlen(path)], "");
	free(path);
	free(real_path);
	return (binary_path);
}

void	init_env_variables(char *shell)
{
	char	*temp_path;
	char	*shell_path;
	char	pwd[SIZE_10B];
	char	*shlvl;
	char	*shlvl_value;

	shlvl = get_env("SHLVL");
	if (shlvl == 0x0)
		shlvl = "0";
	shlvl_value = ft_itoa(ft_atoi(shlvl) + 1);
	temp_path = ft_strjoin("./", shell, "");
	shell_path = get_true_filepath(temp_path);
	ft_set_env_var("SHLVL", shlvl_value, 1);
	ft_set_env_var("SHELL", shell_path, 1);
	if (get_env("PATH") == 0x0)
	{
		getcwd("PWD", SIZE_10B);
		ft_set_env_var("PWD", pwd, 0x1);
	}
	if (chdir(get_env("PWD")) == -1)
		shell_exit(EXIT_FAILURE, strerror(errno));
	cleaner_mr_propre(temp_path, shell_path, shlvl_value);
}

/*
 * Save environment data in accessible memory area.
*/

void	init_bash_env(char *shell, t_env env)
{
	t_env	*shell_env;
	int		len;
	int		i;
	t_env	tmp;

	if (env == 0x0)
		return ;
	i = 0x0;
	len = env_length(env);
	shell_env = get_bash_env();
	if (*shell_env == 0x0)
	{
		tmp = garbage_malloc(sizeof(char *) * (len + 1));
		while (env[i])
		{
			tmp[i] = ft_strdup(env[i]);
			i++;
		}
		tmp[i] = 0x0;
		*shell_env = tmp;
	}
	env = NULL;
	init_env_variables(shell);
}
