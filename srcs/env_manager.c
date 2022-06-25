/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:08:17 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/25 01:16:29 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_chararray(char **array)
{
	int	i;
	
	if (!array)
		return ;
	i = 0x0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	*search_for_env_val(char *var, char *name)
{
	char	*value;
	char	*offset;
	size_t	off_len;

	if (!var || !name)
		return (0x0);
	offset = ft_stringjoin(name, "=");
	if (!offset)
		return (0x0);
	off_len = ft_strlen(offset);
	if (!ft_strncmp(var, offset, off_len))
	{
		value = ft_strdup(var + off_len);
		free(offset);
		if (!value)
			return (0x0);
		return (value);
	}
	free(offset);
	return (0x0);
}

char	*get_env_array(char *name, char **envp)
{
	char	*val;
	char	**p_envp;

	p_envp = envp;
	while (*envp)
	{
		val = search_for_env_val(*p_envp, name);
		if (val)
			return (val);
		p_envp++;
	}
	return (0x0);
}

int	ft_read_char_arr_fd(char ***array, int fd)
{
	int		n;
	char	buff[2];
	char	*tmp;

	n = 0x1;
	tmp = 0x0;
	if (fd)
	{
		while (n > 0x0)
		{
			n = read(fd, buff, 0x1);
			if (n == EOF)
				break;
			if (n == -1)
				return (0x1);
			buff[n] = 0x0;
			tmp = ft_strcat(tmp, buff);
		}
	}
	*array = ft_split(tmp, '\n');
	free(tmp);
		return (0x1);
	return (0x0);
}

char	**env_reader(char *name)
{
	char	**env;
	int		fd;

	if (!name)
		return (0x0);
	fd = open(name, O_RDONLY, 0777);
	if (fd < 0x0)
		return (0x0);
	ft_read_char_arr_fd(&env, fd);
	close (fd);
	if (!env)
		return (0x0);
	return (env);
}
