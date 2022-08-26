/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:11:38 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/26 17:23:30 by ablaamim         ###   ########.fr       */
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

t_redirs	*redirection_generator(char **args)
{
	t_redirs	*new_redir;

	new_redir = malloc(sizeof(*new_redir));
	new_redir->fd[0] = 0x0;
	new_redir->fd[1] = 0x1;
	new_redir->type = 0x0;
	new_redir->file_name = 0x0;
	new_redir->next = 0x0;
	return (new_redir);
}

void	redir_appender(t_redirs *new_redir, t_redirs **lst_redir)
{
	t_redirs	*current;

	if (*lst_redir == 0x0)
		*lst_redir = new_redir;
	else
	{
		current = *lst_redir;
		while (current->next)
			current = current->next;
		current->next = new_redir;
		new_redir->next = NULL;
	}
}


void	print_redir_list(t_redirs *redir)
{
	t_redirs *current;

	current = redir;
	while (current)
	{
		 //printf("| FILE NAME : %s | ", current->file_name);
		 if (current->type == INPUT_REDIR)
		 	printf("| TYPE = INPUT REDIR | ");
		 else if (current->type == OUTPUT_REDIR)
			printf("TYPE = OUTPUT REDIR | ");
		 else if (current->type == HEREDOC_REDIR)
			printf("TYPE = HEREDOC REDIR | ");
		 else
			 printf("TYPE = APPEND REDIR | ");
		 printf("FILE NAME : %s | ", current->file_name);
		 if (current->next == 0x0)
		 	printf("-->NULL\n");
		//printf("%p: %s\n", current, current->file_name);
		current = current->next;
	}
}

t_redirs	*redirections_manager(char **args, int *fd_in, int *fd_out, t_node *node)
{
	t_redirs	*redir;

	// 4 CASES TO HANDLE : '<' '<<' '>' '>>'
	//redir = redirection_generator(args);
	if (strcmp("<", *args) == 0x0)
	{
		redir = redirection_generator(args);
		printf("MANAGING INPUT REDIR : \n");
		//redir = redirection_generator(args);
		if (*fd_in != 0)
			close(*fd_in);
		redir->type = INPUT_REDIR;
		redir->file_name = *(args + 1);
		//print_redir_list(redir);
		//redir_appender(redir, &node->content.simple_cmd.redirs);
		//print_redir_list(node->content.simple_cmd.redirs);
		
	}
	// > && >> IN ONE CONDITIONAL STRUCTURE
	// I WILL STRCMP INPUT WITHIN
	else if (ft_strcmp("<<", *args) == 0x0)
	{
		if (*fd_in != 0)
			close(*fd_in);
		//MANAGE HEREDOC
		printf("MANAGE HEREDOC\n\n");
		redir = redirection_generator(args);
		redir->type = HEREDOC_REDIR;
		redir->file_name = *(args + 1);
	}
	else if (ft_strcmp(">", *args) == 0x0)
	{
		printf("OUTPUT REDIR\n");
		if (*fd_out != 1)
			close(*fd_out);
		//*fd_out = exec_output_redirection(args);
		redir = redirection_generator(args);
		redir->type = OUTPUT_REDIR;
		redir->file_name = *(args + 1);
	}
	else if (ft_strcmp(">>", *args) == 0x0)
	{
		printf("APPEND REDIR\n");
		if (*fd_out != 1)
			close(*fd_out);
		//*fd_out = exec_output_redirection(args);
		redir = redirection_generator(args);
		redir->type = APPEND_OUTPUT_REDIR;
		redir->file_name = *(args + 1);
	}
	//print_redir_list(node->content.simple_cmd.redirs);
	return (redir);
}

// SOLVE INFINITE LOOP BY REMOVING REDIRECTIONS EXECUTED IN STREAM INPUT

void	clear_redirs_from_input(char **input)
{
	int	i;

	i = 2;
	//printf("Clearing redirs from input ...\n");
	while (input[i] != 0x0)
	{
		input[i - 2] = input[i];
		++i;
	}
	input[i - 2] = input[i];
	//printf("%s\n", *input);
}

// PARSE INPUT CMD LOOKING FOR REDIE AND EXEC THEM ACCORDINGLY
bool	open_redir_stream(char **argv, int *fd_in, int *fd_out, t_node *node)
{
	int	i;
	t_redirs *redir;

	i = 0x0;
	while (argv[i] != 0x0)
	{
		// PARSE ALL REDIR TYPES -> STRCMP AND RET A FUCKING BOOL VALUE HEHEHEHE 
		if (parse_redirection(argv[i]) == true)
		{
			// MANAGE ALL REDIRECTIONS :
			// TO DO : EXEC REDIR -> Khass ncomparer l pointeur 3awd LOL
			// -> strcmp -> then exec
			// WHAT IF ANOTHER FD IS OPEN ??
			redir = redirections_manager(&argv[i], fd_in, fd_out, node);

			//printf("fname 0 = %s\n", redir->file_name);
			redir_appender(redir, &node->content.simple_cmd.redirs);
			//printf("fname 1 = %s\n", redir->file_name);
			//print_redir_list(node->content.simple_cmd.redirs);
			// SHIT LOOPS ENDLESS IF I DONT RM REDIRS ...
			// I GOTTA CLEAN INPUT FROM REDIRS AFTER EXECUTING REDIRS
			clear_redirs_from_input(&argv[i]);
		}
		else
			++i;
	}
	print_redir_list(node->content.simple_cmd.redirs);
	return (true);
}

bool	execute_redirections(t_node *node)
{
	if (node->type == SIMPLE_CMD)
	{
		//printf("open_redir_stream and execute it\n\n");
		return (open_redir_stream(node->content.simple_cmd.argv, &node->content.simple_cmd.fd_in, &node->content.simple_cmd.fd_out, node));
	}
	else
	{
		//EXEC SHIT RECUSSIVELY AS LONG AS NODE TYPE IS SIMPLE_CMD
		// RETURN FALSE IF ANOTHER NODE TYPE.
		if (node->content.child.left != 0x0)
		{
			//printf("TREE LEFT TRAVERSAL\n");
			if (execute_redirections(node->content.child.left) == false)
				return (false);
		}
		if (node->content.child.right != 0x0)
		{
			//printf("TREE RIGHT TRAVERSAL\n");
			if (execute_redirections(node->content.child.right) == false)
				return (false);
		}
		return (true);
	}
}
