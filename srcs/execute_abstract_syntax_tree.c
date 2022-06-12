/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_abstract_syntax_tree.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:49:57 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/12 10:17:08 by ablaamim         ###   ########.fr       */
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
 * Execute a simple command.
*/

void	ft_exec_cmd(t_node	*ast)
{
	
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
		ft_exec_cmd(ast);
	}
	else
		printf("To be continued ...\n");
}
