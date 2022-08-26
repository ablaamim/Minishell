/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:43:51 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/26 13:14:19 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Print error, since its a subshell
*/

bool	printerror_and_falsify(bool is_subshell)
{
	if (is_subshell == false)
		variadic_error_printer(2, ERROR_TOKEN);
	else
		variadic_error_printer(2, ERROR_TOKEN);
	return(false);
}

/*
 * Calculate number of args contained in a command
*/

unsigned int	calculate_number_of_args(t_token *token_list)
{
	unsigned int	nb_cmd;
	t_token			*current;

	nb_cmd = 0x0;
	current = token_list;
	while (current != 0x0 && identify_leaf(current->type) == true)
	{
		++nb_cmd;
		current = current->next;
	}
	return (nb_cmd);
}

/*
 * convert arguments in a token from a list into an array.
*/

bool	convert_list_to_array(t_token **token_list, t_node \
		*simple_command, bool is_subshell)
{
	int	i;

	i = 0x0;
	simple_command->content.simple_cmd.argv = garbage_malloc(sizeof(char *) * 
			((calculate_number_of_args(*token_list) + 1)));
	ft_bzero(simple_command->content.simple_cmd.argv,
			sizeof(simple_command->content.simple_cmd.argv));
	while (*token_list != 0x0 && identify_leaf((*token_list)->type) == true)
	{
		if (identify_redirection((*token_list)->type) == true &&\
				((*token_list)->next == 0x0 || (*token_list)->next->type \
				!= WORD_TOKEN))
		{
			token_devour(token_list);
			if (*token_list == 0x0)
				return(printerror_and_falsify(is_subshell));
			if ((*token_list)->type != WORD_TOKEN)
				return (false);
		}
		simple_command->content.simple_cmd.argv[i++] = \
				ft_strdup(((*token_list)->data));
		token_devour(token_list);
	}
	simple_command->content.simple_cmd.argv[i] = 0x0;
	return (true);
}

/*
 * executing simple_command_parser() sacanner looking for a simple command,
 * -> if the token is not a leaf, it is the end of the automata,
 *   the simple command node is allocated.
 * -> the number of arguments of this command is retrieved via retrieve argc,
 * -> list_to_array fills the argv array.
 *
 * [TO DO] : TRACK SEVG AND GET RIDE OF IT
 *
*/

bool	simple_command_parser(t_token **token_list, t_node **ast, \
		bool is_subshell)
{
	t_node	*simple_command;
/*
	if ((*token_list)->type == CLOSE_PARENTH_TOKEN)
		return (false);
	else if ((*token_list)->type == OP_PARENTH_TOKEN)
		return (false);
*/
	if (identify_leaf((*token_list)->type) == false)
		return (false);
	simple_command = 0x0;
	simple_command = garbage_malloc(sizeof(*simple_command));
	ft_bzero(simple_command, sizeof(*simple_command));
	simple_command->type = SIMPLE_CMD;
	simple_command->content.simple_cmd.fd_in = 0;
	simple_command->content.simple_cmd.fd_out = 1;
	simple_command->content.simple_cmd.redirs = 0x0;
	if (convert_list_to_array(token_list, simple_command, is_subshell) == \
			false)
		return (false);
	*ast = simple_command;
	return (true);
}
