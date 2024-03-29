/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:06:55 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 11:33:55 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function to print ENV.
*/

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

/*
 * Function to debug linked list
*/

void	print_helper_linked_list(t_token *current_token)
{
	if (current_token->type == WORD_TOKEN)
		printf("[ Type = %s", "WORD_TOKEN");
	else if (current_token->type == DLESSER_TOKEN)
		printf(("[ Type = %s"), "DLESSER_TOKEN");
	else if (current_token->type == LESSER_TOKEN)
		printf("[ Type = %s", "LESSER_TOKEN");
	else if (current_token->type == DGREATER_TOKEN)
		printf("[ Type = %s", "DGREATER_TOKEN");
	else if (current_token->type == GREATER_TOKEN)
		printf("[ Type = %s", "GREATER_TOKEN");
	else if (current_token->type == AND_TOKEN)
		printf("[type = %s", "AND_TOKEN");
	else if (current_token->type == SEMICO_TOKEN)
		printf("[ type = %s", "SEMICO_TOKEN");
	else if (current_token->type == PIPE_TOKEN)
		printf("[ type = %s", "PIPE_TOKEN");
	else if (current_token->type == OR_TOKEN)
		printf("[ type = %s", "OR_TOKEN");
	else if (current_token->type == OP_PARENTH_TOKEN)
		printf("[ type = %s", "OP_PARENTH_TOKEN");
	else if (current_token->type == CLOSE_PARENTH_TOKEN)
		printf("[ type = %s", "CLOSE_PARENTH_TOKEN");
}

void	ft_print_token(t_token *token)
{
	t_token	*current_token;

	current_token = garbage_malloc(sizeof(token));
	current_token = token;
	while (current_token != 0x0)
	{
		print_helper_linked_list(current_token);
		printf(" | Data = ~ %s ~] ------> ", current_token->data);
		current_token = current_token->next;
	}
	if (current_token == 0x0)
		printf("(NULL)\n\n");
}

void	print_helper_tree(t_node *tree1)
{
	int	i;

	i = 0x0;
	if (tree1->type == OR_NODE)
		printf("OR_NODE\n");
	else if (tree1->type == AND_NODE)
		printf("AND_NODE\n");
	else if (tree1->type == PIPE_NODE)
		printf("PIPE_NODE\n");
	else if (tree1->type == SEMICO_NODE)
		printf("SEMICO_NODE\n");
	else
	{
		if (tree1->content.simple_cmd.argv != NULL)
		{
			i = 0x0;
			printf("SIMPLE_CMD: ");
			while (tree1->content.simple_cmd.argv[i])
			{
				printf("%s ", tree1->content.simple_cmd.argv[i]);
				i++;
			}
			printf("\n");
		}
	}
}

/*
 * Tree traversal and nodes printing.
*/

void	disp_tree(t_node *tree, int lev)
{
	t_node	*tree1;
	int		i;

	i = 0x0;
	tree1 = garbage_malloc(sizeof(t_node));
	tree1 = tree;
	if (tree1 == 0x0)
		return ;
	while (i < lev)
	{
		printf("\t\t");
		i++;
	}
	print_helper_tree(tree1);
	disp_tree(tree1->content.child.right, lev + 1);
	disp_tree(tree1->content.child.left, lev + 1);
	printf("\n");
}
