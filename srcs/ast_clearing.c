/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_clearing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:32:23 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/05 23:06:08 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ast_clearing(t_node **ast)
{
	if (*ast == 0x0)
		return ;
	if ((*ast)->type == SIMPLE_CMD)
		simple_cmd_clearing(ast);
	else
	{
		ast_clearing(&(*ast)->content.child.left);
		ast_clearing(&(*ast)->content.child.right);
		garbage_free((void **)&*ast);
	}
}

void	ft_lstadd_back(t_pipe **alst, t_pipe *new)
{
	t_pipe	*last;

	if (new != NULL)
	{
		if (ft_lstsize(*(alst)) > 0)
		{
			last = ft_lstlast(*(alst));
			last->next = new;
		}
		else
			ft_lstadd_front(alst, new);
	}
}

int	ft_is_child_ignored(char *string)
{
	int		i;
	char	**built_ins;
	int		ignored;

	i = 0;
	ignored = 0;
	built_ins = ft_split("cd unset export exit echo", ' ');
	while (built_ins[i])
	{
		if (built_ins[0] == 0x0 || string == 0x0)
			break ;
		if (!ft_strcmp(built_ins[i], string))
			ignored = 1;
		i++;
	}
	i = 0;
	while (built_ins[i])
		free(built_ins[i++]);
	free(built_ins);
	return (ignored);
}

void	ft_clean_support(t_node *node, char *new_argv)
{
	int	i;

	i = 0;
	while (node->content.simple_cmd.argv[i])
		free(node->content.simple_cmd.argv[i++]);
	free(node->content.simple_cmd.argv);
	node->content.simple_cmd.argv = ft_split(new_argv, '|');
	free(new_argv);
}

void	ft_clean_argv(t_node *node)
{
	int		has_wildc;
	char	*new_argv;
	char	*tmp;
	int		i;

	has_wildc = 0;
	new_argv = ft_strdup("");
	i = 0;
	tmp = NULL;
	while (node->content.simple_cmd.argv[i])
	{
		if (ft_strchr(node->content.simple_cmd.argv[i], '*') && \
				ft_argv_len(node->content.simple_cmd.argv) > 2)
			has_wildc = 1;
		else
		{
			tmp = ft_strdup(new_argv);
			free(new_argv);
			new_argv = ft_strjoin(tmp, node->content.simple_cmd.argv[i], "|");
			free(tmp);
		}
		i++;
	}
	if (has_wildc)
		ft_clean_support(node, new_argv);
}
