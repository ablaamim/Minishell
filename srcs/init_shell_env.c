/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:18:54 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/17 18:20:18 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*path_extracter(char const	*filepath)
{
	int	i;

	if (filepath == 0x0)
		return (0x0);
	if (ft_strchr(filepath, '/') == 0x0)
		return (ft_strdup("./"));
	i = ft_strlen(filepath);
	while (i > 0 && filepath[i] != '/')
		i--;
	printf("%s\n", filepath);
	return (ft_strndup(filepath, i));
}

char	*realpath_helper(char const	*path)
{
	char	*real_path;

	if (ft_strchr(path, '/') == 0x0 && chdir("./") == -1)
		return (0x0);
	if (chdir(path) == -1)
		return (0x0);
	real_path = getcwd(0x0, 0x0);
	if (real_path == 0x0)
	{
		printf("EXIT SHELL\n");
		exit(EXIT_FAILURE);
	}
	return (real_path);
}

char	*get_true_filepath(char const	*filepath)
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
	printf("%s\n", binary_path);
	garbage_free((void **) &path);
	free(real_path);
	return (binary_path);
}

void	init_env_variables(char *shell)
{
	char	*temp_path;
	char	*shell_path;

	temp_path = ft_strjoin("./", shell, "");
	shell_path = get_true_filepath(temp_path);
	if (get_env("PATH") == 0x0)
	{
		printf("Problematic!!");
		exit(EXIT_FAILURE);
	}
}

int	init_bash_env(char *shell, t_env	env)
{
	t_env	*shell_env;
	int		len;
	int		i;
	t_env	tmp;

	i = 0x0;
	len = env_length(env);
	shell_env = get_bash_env();
	if (*shell_env == 0x0)
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = 0x0;
	*shell_env = tmp;
	init_env_variables(shell);
	return (0x0);
}
