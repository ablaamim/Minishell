/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:06:55 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/11 09:12:36 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function to print all of the env variables
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

void	ft_print_token(t_token *token)
{
	t_token	*current_token;

	if (token == 0x0)
		printf("Linked list is empty\n");
	current_token = garbage_malloc(sizeof(token));
	current_token = token;
	while (current_token != 0x0)
	{
		if (current_token->type == WORD_TOKEN)
			printf("[ Type = %s", "WORD_TOKEN");
		else if (current_token->type == LESSER_TOKEN)
			printf(("[ Type = %s"), "LESSER_TOKEN");
		else if (current_token->type == DLESSER_TOKEN)
			printf("[ Type = %s", "DLESSER_TOKEN");
		else if (current_token->type == GREATER_TOKEN)
			printf("[ Type = %s", "GREATER_TOKEN");
		else if (current_token->type == DGREATER_TOKEN)
			printf("[ Type = %s", "DGREATER_TOKEN");
		else if (current_token->type == AND_CHAR)
			printf("[type = %s", "AND_TOKEN");
		else if (current_token->type == SEMICO_TOKEN)
			printf("[ type = %s", "SEMICO_CHAR");
		else if (current_token->type == PIPE_TOKEN)
			printf("[ type = %s", "PIPE_TOKEN");
		else if (current_token->type == OR_TOKEN)
			printf("[ type = %s", "OR_TOKEN");
		else if (current_token->type == OP_PARENTH_TOKEN)
			printf("[ type = %s", "OP_PARENTH_TOKEN");
		else if (current_token->type == CLOSE_PARENTH_TOKEN)
			printf("[ type = %s", "CLOSE_PARENTH_CHAR");
		printf(" | Data = ~ %s ~] ------> ", current_token->data);
		current_token = current_token->next;
	}
	if (current_token == 0x0)
		printf("(NULL)");
}

void	disp_tree(t_node	*tree, int	lev)
{
	if (tree == 0x0)
		return ;
	//if (tree != 0x0)
	//	printf("All good !\n");
	//[INORDER NODE TRAVERSAL]
	//disp_tree(tree->content.child.left, lev + 1);
	//disp_tree(tree->content.child.right, lev + 1);
	for (int i = 0; i < lev; i++)
		printf("\t\t");
	if (tree->type == OR_NODE )
		printf("OR_NODE\n");
	else if (tree->type == AND_NODE)
		printf("AND_NODE\n");
	else if (tree->type == PIPE_NODE)
		printf("PIPE_NODE\n");
	else if (tree->type == SEMICO_NODE)
		printf("SEMICO_NODE\n");
	else if (tree->type == SIMPLE_CMD && tree->content.type == 1)
	{
		if(tree->content.simple_cmd.argv != NULL)
		{
			printf("SIMPLE_CMD: ");
			for (int i = 0; tree->content.simple_cmd.argv[i]; i++)
			{
				printf("%s", tree->content.simple_cmd.argv[i]);
			}
			printf("\n");
		}
	}
	else
	{
		printf("UNKOWN\n");
		exit(EXIT_FAILURE);
	}
	//[PREORDER NODE TRAVERSAL]
	disp_tree(tree->content.child.left, lev + 1);
	disp_tree(tree->content.child.right, lev + 1);
	printf("\n");
}
