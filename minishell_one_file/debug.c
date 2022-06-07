/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:06:55 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/07 17:35:31 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_display_ast(t_node *ast, int level)
{
	int	i;

	if (ast == 0x0)
		return ;
	i = 0x0;
	while (i < level)
	{
		printf("\t\t");
		i++;
	}
	if (ast->type == SIMPLE_CMD)
		printf("SIMPLE_CMD\n");
	else if (ast->type == PIPE_NODE)
		printf("PIPE_NODE\n");
	else
		printf("UNKNOWN COMMAND\n");
	ft_display_ast(ast->content.child.left, level + 1);
	ft_display_ast(ast->content.child.right, level + 1);
}

void	ft_print_env(char **env)
{
	int	param;

	if (!*env || !env)
		exit(EXIT_FAILURE);
	param = 0x0;
	while (env[param])
	{
		printf("%s\n", env[param]);
		param++;
	}
}
