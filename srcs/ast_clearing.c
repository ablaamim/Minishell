/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_clearing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:32:23 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/19 16:56:38 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ast_clearing(t_node	**ast)
{
	if (*ast == 0x0)
		return ;
	if ((*ast)->type = SIMPLE_CMD)
		simple_cmd_clearing(ast);
	else
	{
		ast_clearing(&(*ast)->content.child.left);
		ast_clearing(&(*ast)->content.child.right);
		free(*ast);
	}
}
