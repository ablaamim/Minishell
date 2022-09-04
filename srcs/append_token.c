/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:59:08 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/04 21:02:08 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Add the new_token to the linked list.
*/

void	append_token(t_token *new_token, t_token **token_list)
{
	t_token	*current;

	if (*token_list == 0x0)
		*token_list = new_token;
	else
	{
		current = *token_list;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

int ft_argv_len(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

t_pipe *ft_lstlast(t_pipe *lst)
{
	if (ft_lstsize(lst) == 0)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void ft_lstadd_front(t_pipe **head, t_pipe *new)
{
	new->next = *(head);
	*(head) = new;
}

t_pipe *ft_lstnew(int *fd)
{
	t_pipe *lst;

	lst = (t_pipe *)malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->fd[0] = fd[0];
	lst->fd[1] = fd[1];
	lst->next = NULL;
	return (lst);
}