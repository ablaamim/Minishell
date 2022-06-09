/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:06:55 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/09 16:37:48 by ablaamim         ###   ########.fr       */
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
	if (!token)
	{
		garbage_memdel((void **) &token);
		write(2, MALLOC_ERROR, sizeof(MALLOC_ERROR));
	}
	current_token = token;
	while (current_token != 0x0)
	{
		if (current_token->type == WORD_TOKEN)
			printf("( TYPE : %s)", "WORD_TOKEN");
		printf("|| DATA : (%s)|----> ", current_token->data);
		current_token = current_token->next;
	}
}
