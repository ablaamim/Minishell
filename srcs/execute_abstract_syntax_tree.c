/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_abstract_syntax_tree.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:49:57 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/12 12:49:10 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * To do :
*/

/*
 * Define my execution core function, use it in inline_mode.
*/

/*
 * I will start by executing a simple command, then try to execute redir, pipes
 * and so on ...
*/

/*
 * execute a simple command.
*/

/*
void	ft_exec_simple_cmd(t_simple_cmd	cmd)
{
	pid_t	pid;


	if ()
	{
		
	}
}
*/

/*
 * Execute a simple command.
*/

void	ft_complex_exec(t_node	*ast)
{
	//ft_exec_simple_cmd(ast->content.simple_cmd);
}
/*
 * Core function of my executor.
*/

void	execute_ast_data(t_node	*ast, bool	inline_mode)
{
	//printf("%d\n", inline_mode);
	if (inline_mode == false)
		write(2, "\n\r", 2);
	if (ast->type == SIMPLE_CMD)
	{
		printf("SIMPLE CMD EXECUTION : \n\n");
		ft_complex_exec(ast);
	}
	else
		printf("To be continued [EXECUTION STAGE]...\n");
}
