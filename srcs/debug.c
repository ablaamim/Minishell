/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:06:55 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/11 09:43:02 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Display simple command content.
*/

void	ft_print_simple_cmd(char	**argv)
{
	int	argc;

	argc = 0x0;
	while (argv[argc])
	{
		printf("%s  ", argv[argc]);
		argc++;
	}
	printf("\n\n");
}

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

void	ft_print_token(t_token *token)
{
	t_token	*current_token;

	current_token = malloc(sizeof(token));
	current_token = token;
	while (current_token != 0x0)
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
		printf(" | Data = ~ %s ~] ------> ", current_token->data);
		current_token = current_token->next;
	}
	if (current_token == 0x0)
		printf("(NULL)\n\n");
}

void	disp_tree(t_node *node, int lev)
{
	t_node	*current_node;

	if (node == 0x0)
		return ;
	current_node  = malloc(sizeof(t_node));
	current_node = node;
	for (int i = 0; i < lev; i++)
		printf("\t\t");
	if (current_node->type == OR_NODE)
		printf("OR_NODE\n");
	else if (current_node->type == AND_NODE)
		printf("AND_NODE\n");
	else if (current_node->type == PIPE_NODE)
		printf("PIPE_NODE\n");
	else if (current_node->type == SEMICO_NODE)
		printf("SEMICO_NODE\n");
	else if (current_node->type == SIMPLE_CMD && current_node->content.type == 1)
	{
		if(current_node->content.simple_cmd.argv != NULL)
		{
			printf("SIMPLE_CMD: ");
			for (int i = 0; current_node->content.simple_cmd.argv[i]; i++)
			{
				printf("%s ", current_node->content.simple_cmd.argv[i]);
			}
			printf("\n");
		}
	}
	else
	{
		variadic_error_printer(2, "ERROR : UNKNOWN DATA\n");
		exit(EXIT_FAILURE);
	}
	disp_tree(current_node->content.child.right, lev + 1);
	disp_tree(current_node->content.child.left, lev + 1);
	printf("\n");
}
