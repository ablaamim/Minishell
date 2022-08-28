/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:55:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 12:23:05 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Tokenize the LESSER_TOKEN AND DLESSER_TOKEN.
*/

/*
bool	ft_srch(char *inchars, char c)
{
	int	iter;

	iter = 0x0;
	while (inchars[iter])
	{
		if (inchars[iter] == c)
			if (inchars[iter + 0x1] == c)
				return (true);
		iter++;
	}
	return (false);
}
*/

t_redirs	*redir_generator(char *in_characters, enum e_redirection_type \
		red_type)
{
	t_redirs	*new_redir;

	new_redir = garbage_malloc(sizeof(*new_redir));
	new_redir->fd[0] = 0x0;
	new_redir->fd[1] = 0x1;
	new_redir->type = red_type;
	new_redir->file_name = in_characters;
	new_redir->next = 0x0;
	return (new_redir);
}

void	vizualize_redir_node(t_redirs *redir)
{
	printf("[ fd in : %d | ", redir->fd[0]);
	printf("fd out : %d | ", redir->fd[1]);
	printf("file name : %s | ", redir->file_name);
	if (redir->type == HEREDOC_REDIR)
		printf("HEREDOC_REDIR ]\n");
}

void	append_redir_list(t_redirs *new_redir, t_redirs **redir_list)
{
	t_redirs	*current;

	if (*redir_list == 0x0)
		*redir_list = new_redir;
	else
	{
		current = *redir_list;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

t_token	*tokenize_lesser(char *in_characters, int *i)
{
	char					*data;
	enum e_token_type		type;

	if (define_char_type(in_characters[++(*i)]) == LESS_CHAR)
	{
		data = garbage_malloc(sizeof(data) * 3);
		ft_strlcpy(data, "<<", 3);
		type = DLESSER_TOKEN;
		++(*i);
	}
	else
	{
		data = garbage_malloc(sizeof(data) * 2);
		ft_strlcpy(data, "<", 2);
		type = LESSER_TOKEN;
	}
	return (token_generator(data, type));
}

t_token	*tokenize_greater(char *in_characters, int *i)
{
	char				*data;
	enum e_token_type	type;

	if (define_char_type(in_characters[++(*i)]) == GREAT_CHAR)
	{
		data = garbage_malloc(sizeof(*data) * SIZEOF_TWO_CHAR_STRING);
		ft_strlcpy(data, ">>", SIZEOF_TWO_CHAR_STRING);
		type = DGREATER_TOKEN;
		++(*i);
	}
	else
	{
		data = garbage_malloc(sizeof(*data) * SIZEOF_ONE_CHAR_STRING);
		ft_strlcpy(data, ">", SIZEOF_ONE_CHAR_STRING);
		type = GREATER_TOKEN;
	}
	return (token_generator(data, type));
}
