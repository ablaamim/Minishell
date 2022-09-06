/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_char_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:31:54 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 17:44:11 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

enum e_char_rules	apply_rules(enum e_char_type char_type)
{
	enum e_char_rules const	apply_rules[] = {
	[NULL_CHAR] = NOT_ACCEPTED,
	[ANY_CHAR] = ACCEPTED,
	[SPACE_CHAR] = NOT_ACCEPTED,
	[SQUOTE_CHAR] = ACCEPTED,
	[DQUOTE_CHAR] = ACCEPTED,
	[LESS_CHAR] = NOT_ACCEPTED,
	[GREAT_CHAR] = NOT_ACCEPTED,
	[AND_CHAR] = NOT_ACCEPTED,
	[SEMICO_CHAR] = NOT_ACCEPTED,
	[PIPE_CHAR] = NOT_ACCEPTED,
	[OP_PARENTH_CHAR] = NOT_ACCEPTED,
	[CLOSE_PARENTH_CHAR] = NOT_ACCEPTED
	};

	return (apply_rules[char_type]);
}

enum e_char_type	define_char_type(char c)
{
	enum e_char_type const	char_type[128] = {
		ANY_CHAR,
	['\t'...'\r'] = SPACE_CHAR,
	[' '] = SPACE_CHAR,
	['\"'] = DQUOTE_CHAR,
	['&'] = AND_CHAR,
	['\''] = SQUOTE_CHAR,
	['('] = OP_PARENTH_CHAR,
	[')'] = CLOSE_PARENTH_CHAR,
	[';'] = SEMICO_CHAR,
	['<'] = LESS_CHAR,
	['>'] = GREAT_CHAR,
	['|'] = PIPE_CHAR
	};

	if (c == '\0')
		return (NULL_CHAR);
	return (char_type[(int) c]);
}

void	ft_iterate_tree(t_node *node, t_pipe **pipe_, int *exec_index)
{
	if (expansions_perform(node, 0) == true)
	{
		if (execute_redirections(node) == true)
		{
			ft_hanlde_iteration(node, pipe_, exec_index);
		}
		else
			exit_value_set(EXIT_FAILURE);
	}
	else
		exit_value_set(EXIT_FAILURE);
}
