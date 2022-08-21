/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:11:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/21 16:49:28 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * in simple_cmd there is data that you will need to manage redirections.
 * ->input_stream.
 * ->output_stream.
 * ->boolean value that determines if input stream has single or double quotes
*/

bool	parse_redirection(char *argument)
{
	// Bool : Ya reb7a ya deb7a
	return (ft_strcmp(">", argument) == 0x0 || ft_strcmp(">>", argument) == 0x0 || ft_strcmp("<", argument) == 0x0 || ft_strcmp("<<", argument) == 0x0);
}

bool	redirections_manager(char **args, int *fd_in, int *fd_out, bool input_has_quotes)
{
	(void) input_has_quotes;
	// 4 CASES TO HANDLE : '<' '<<' '>' '>>'
	printf("ANNIE ARE YOU OK? ARE YOU OK ANNIE?\n");
	if (strcmp("<", *args) == 0x0)
	{
		if (*fd_in != 0)
			close(*fd_in);
		*fd_in = exec_input_redirection(*(args + 1));
		if (*fd_in == ERR)
			return (false);
	}
	// > && >> IN ONE CONDITIONAL STRUCTURE
	// I WILL STRCMP INPUT WITHIN
	else if (ft_strcmp("<<", *args) == 0x0)
	{
		if (*fd_in != 0)
			close(*fd_in);
		//MANAGE HEREDOC
		printf("MANAGE HEREDOC\n\n");
		if (*fd_in == ERR)
			return (false);
	}
	else
	{
		printf("LEAVE ME ALONE\n");
		if (*fd_out != 1)
			close(*fd_out);
		*fd_out = exec_output_redirection(args);
		if (*fd_out == ERR)
			return (false);
	}
	return (true);
}

// SOLVE INFINITE LOOP BY REMOVING REDIRECTIONS EXECUTED IN STREAM INPUT

void	clear_redirs_from_input(char **input)
{
	int	i;

	i = 2;
	while (input[i] != 0x0)
	{
		input[i - 2] = input[i];
		++i;
	}
	input[i - 2] = input[i];
}

// PARSE INPUT CMD LOOKING FOR REDIE AND EXEC THEM ACCORDINGLY
bool	open_redir_stream(char **argv, int *fd_in, int *fd_out, bool input_has_quotes)
{
	int	i;

	i = 0x0;
	(void) input_has_quotes;
	while (argv[i] != 0x0)
	{
		// PARSE ALL REDIR TYPES -> STRCMP AND RET A FUCKING BOOL VALUE HEHEHEHE 
		if (parse_redirection(argv[i]) == true)
		{
			// MANAGE ALL REDIRECTIONS :
			// TO DO : EXEC REDIR -> Khass ncomparer l pointeur 3awd LOL
			// -> strcmp -> then exec
			// WHAT IF ANOTHER FD IS OPEN ??
			if (redirections_manager(&argv[i], fd_in, fd_out, input_has_quotes) == false)
				return (false);
			// SHIT LOOPS ENDLESS IF I DONT RM REDIRS ...
			// I GOTTA CLEAN INPUT FROM REDIRS AFTER EXECUTING REDIRS
			clear_redirs_from_input(&argv[i]);
		}
		else
			++i;
	}
	return (true);
}

bool	execute_redirections(t_node *node)
{
	if (node->type == SIMPLE_CMD)
	{
		//printf("open_redir_stream and execute it\n\n");
		return (open_redir_stream(node->content.simple_cmd.argv, &node->content.simple_cmd.fd_in, &node->content.simple_cmd.fd_out, node->content.simple_cmd.input_has_quotes));
	}
	else
	{
		//EXEC SHIT RECUSSIVELY AS LONG AS NODE TYPE IS SIMPLE_CMD
		// RETURN FALSE IF ANOTHER NODE TYPE.
		if (node->content.child.left != 0x0)
			if (execute_redirections(node->content.child.left) == false)
				return (false);
		if (node->content.child.right != 0x0)
			if (execute_redirections(node->content.child.right) == false)
				return (false);
		return (true);
	}
}
