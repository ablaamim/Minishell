/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_parser_program.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:40:32 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/07 19:20:32 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *
*/

t_node	*ft_lexer_parser_program(char *line)
{
	t_node	*ast;

	ast = NULL;
	ast->type = SIMPLE_CMD;
	printf("%d\n", ast->type);
	//ft_display_ast(ast, 0);
	return (ast);
}
