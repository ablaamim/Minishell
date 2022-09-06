/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:59:28 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 23:00:24 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var(char *var_name)
{
	t_env	env;
	char	*tmp;
	int		i;
	int		j;

	env = *get_bash_env();
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		tmp = ft_strdup(env[i]);
		tmp[j] = '\0';
		if (!ft_strcmp(tmp, var_name))
			return (env[i] + (j + 1));
		free(tmp);
		i++;
	}
	return (NULL);
}

void	ft_handle_prompt(char **line)
{
	char	*tmp;
	char	*data;
	char	*data_tmp;
	int		i;

	data_tmp = get_var("PWD");
	tmp = get_var("HOME");
	i = 0;
	printf("\033[0;32m");
	while (data_tmp && tmp && data_tmp[i] && data_tmp[i] == tmp[i])
		i++;
	if (data_tmp && tmp && ft_strlen(tmp) > ft_strlen(data_tmp))
		i = 0;
	else
		data_tmp = ft_strjoin("~", data_tmp + i, "");
	data = ft_strjoin(get_var("USER"), get_var("NAME"), "@");
	tmp = ft_strjoin(data, data_tmp, "\033[0;37m:\033[0;36m");
	free(data);
	data = ft_strjoin(tmp, "\033[0;37m$ ", "");
	free(*line);
	*line = ft_strdup(data);
	free(tmp);
	free(data);
}
