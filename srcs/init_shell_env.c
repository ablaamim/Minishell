/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:18:54 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/18 15:33:32 by ablaamim         ###   ########.fr       */
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
	//printf("===> FILE PATH : %s\n", filepath);
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
		printf("EXIT SHELL : FAILED TO GET PWD\n");
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
	//printf("%s\n", binary_path);
	garbage_free((void **) &path);
	free(real_path);
	return (binary_path);
}

/*
 * Init all environment variable and save them in accessible memory.
 * [SEGV CASE CLOSED, DIN DYMAK!]
*/

void	init_env_variables(char	*shell)
{
	char	*temp_path;
	char	*shell_path;
	char	*shlvl;
	char	*shlvl_value;

	shlvl = get_env("SHLVL");
	if (shlvl == 0x0)
		shlvl = "0";
	//printf("%s\n", shlvl); [DEBUG CURRENT DATA]
	//exit(EXIT_FAILURE);
	shlvl_value = ft_itoa(ft_atoi(shlvl) + 1);
	temp_path = ft_strjoin("./", shell, "");
	//printf("==> TEMP_PATH : %s\n", temp_path);
	//exit(EXIT_FAILURE);
	shell_path = get_true_filepath(temp_path);
	//printf("==> SHLVL VALUE : %s\n", shlvl_value);
	//printf("==> SHELL_PATH : %s", shell_path);
	//exit(EXIT_FAILURE);
	//GOTTA CREATE A SET_ENV() FUNCTION.
	ft_set_env_var("SHLVL", shlvl_value, 1);
	ft_set_env_var("SHELL", shell_path, 1);
	//printf("\n\n=====> DAFUQ \n\n");
	//exit(EXIT_FAILURE);
	if (getenv("PATH") == 0x0)
		ft_set_env_var("PATH", PATH_AS_DEFAULT, 1);
	//printf("\n\n====> DAFUQ!! \n\n");
	//cleaner_mr_propre(temp_path, shell_path, shlvl_value);
}

/*
 * Save environment data in memory so i can access it.
 * [STUPID MISTAKE IN STRDUP, I REPLACED IT]
 * [THIS IS FUCKED UP, FOCUCE BROSKI]
 * [CASE CLOSED FINALLY.]
*/

int	init_bash_env(char	*shell, t_env	env)
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
		tmp = garbage_malloc(sizeof(char *) * (len + 1));
		while (env[i])
		{
			tmp[i] = ft_strdup(env[i]);
			//printf("%s\n", tmp[i]); // CASE CLOSED.
			i++;
		}
		tmp[i] = 0x0;
		*shell_env = tmp;
	}
	//printf("==> SHELL : %s\n", shell);
	init_env_variables(shell);
	return (0x0);
}
