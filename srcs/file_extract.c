/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:10:15 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/05 23:50:02 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*file_extract(char *filepath)
{
	int	i;

	if (filepath == 0x0)
		return (0x0);
	if (ft_strchr(filepath, '/') == 0x0)
		return (filepath);
	i = ft_strlen(filepath);
	while (i > 0 && filepath[i] != '/')
		i--;
	return (&filepath[i + 1]);
}

void	display_env(t_node *node)
{
	int		i;
	t_env	*env;

	env = get_bash_env();
	i = 0x0;
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '=') != 0x0)
			variadic_error_printer(node->content.simple_cmd.fd_out, \
					"declare -x %s\n", (*env)[i]);
		else
			variadic_error_printer(node->content.simple_cmd.fd_out, \
					"%s\n", (*env)[i]);
		i++;
	}
}

int	**ft_to_array(t_pipe **pipe)
{
	int		i;
	t_pipe	*tmp;
	int		**arr;

	arr = malloc(sizeof(int *) * ft_lstsize(*pipe));
	if (!arr)
		variadic_error_printer(2, "Error : malloc() failed\n");
	i = 0;
	while (i < ft_lstsize(*pipe))
		arr[i++] = malloc(sizeof(int) * 2);
	i = 0;
	tmp = *pipe;
	while (tmp)
	{
		arr[i][0] = tmp->fd[0];
		arr[i][1] = tmp->fd[1];
		tmp = tmp->next;
		i++;
	}
	return (arr);
}

void	ft_free_to_array(t_pipe **pipe, int **arr)
{
	int	i;

	i = 0;
	while (i < ft_lstsize(*pipe))
		free(arr[i++]);
	free(arr);
}

void	ft_close_pipes(t_pipe *pipe, int **arr)
{
	int	i;
	int	j;

	i = 0;
	while (i < ft_lstsize(pipe))
	{
		j = 0;
		while (j < 2)
			close(arr[i][j++]);
		i++;
	}
}
