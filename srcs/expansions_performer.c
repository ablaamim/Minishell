/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_performer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:31:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 21:24:02 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	expander(t_simple_cmd *cmd, int remove_quotes)
{
	int	i;

	i = 0x0;
	if (!remove_quotes)
		return (true);
	while (cmd->argv[i] != 0x0)
	{
		if (ft_strchr(cmd->argv[i], '$') != 0x0 && !(i > 0x0
				&& ft_strcmp(cmd->argv[i - 1], "<<") == 0x0))
		{
			if (variable_expansion(cmd, i) == false)
				return (false);
		}
		++i;
	}
	i = 0x0;
	while (cmd->argv[i] != 0x0)
	{
		if (ft_strcmp(cmd->argv[i], "<<") == 0x0)
			cmd->input_has_quotes = (ft_strchr(cmd->argv[i + 1], '\'') != 0x0
					|| ft_strchr(cmd->argv[i + 1], '"') != 0x0);
		remove_quotes_from_argument(&cmd->argv[i]);
		++i;
	}
	return (true);
}

/*
 * Perform expansions recursively !!
 */

bool	expansions_perform(t_node *ast, int remove_quotes)
{
	if (ast && ast->type == SIMPLE_CMD)
		return (expander(&ast->content.simple_cmd, remove_quotes));
	else
	{
		if (ast->content.child.left != 0x0)
		{
			if (expansions_perform(ast->content.child.left,
					remove_quotes) == false)
				return (false);
		}
		if (ast->content.child.right != 0x0)
		{
			if (expansions_perform(ast->content.child.right,
					remove_quotes) == false)
				return (false);
		}
	}
	return (true);
}

void	append_to_env(char *export, char *var_name)
{
	bool	replace;
	char	*ptr;
	char	*env_val;
	char	*var_val;

	replace = true;
	var_val = 0x0;
	ptr = ft_strchr(export, '=');
	env_val = get_env(var_name);
	if (ptr == 0x0)
	{
		var_val = 0x0;
		if (env_val != 0x0 && env_val[-1] == '=')
			replace = false;
	}
	else
		var_val = retrieve_var_val(ptr + 1, env_val);
	if (replace == true)
		ft_set_env_var(var_name, var_val, 0x1);
	garbage_free((void **)&var_val);
}
