/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:10:06 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/28 12:00:47 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expander_utils_initializer(char **argv, char **splitted_variable, \
		char *var_val, t_expander *utils)
{
	utils->len_old_argv = retrieve_len_array(argv);
	utils->len_argv_to_append = retrieve_len_array(splitted_variable);
	utils->len_new_argv = utils->len_old_argv + utils->len_argv_to_append - \
						(utils->first_joined == false) - \
						(utils->last_joined == false) + \
						(utils->has_space == true);
	utils->i_old = 0x0;
	utils->i_new = 0x0;
	utils->i_split = 0x0;
	utils->has_space = has_space(var_val);
	utils->first_joined = (ft_isspace(var_val[0]) == 0x0);
	utils->last_joined = (ft_isspace(var_val[ft_strlen(var_val) - 1]) == 0x0);
}

bool	argument_is_redirection(char *arg)
{
	return (ft_strcmp(">", arg) == 0 || ft_strcmp(">>", arg) == 0
		|| ft_strcmp("<", arg) == 0 || ft_strcmp("<<", arg) == 0);
}

bool	verify_validity(int i, char ***splitted_variable, \
		char **argv)
{
	printf("\n\n\nLOL\n");
	if (i > 0 && retrieve_len_array(*splitted_variable) > 1 && \
			argument_is_redirection(argv[i - 1]) == true)
	{
		variadic_error_printer(2, "minishell : %s : ambiguous redirection ", \
				argv[i]);
		garbage_free((void **) splitted_variable);
		return (false);
	}
	return (true);
}

bool	ft_reallocate_arg(t_simple_cmd *cmd, int i, int *j, char *var_val)
{
	char		**new_argv;
	char		**splitted_var;
	t_expander	utils;

	splitted_var = ft_split(var_val, ' ');
	if (verify_validity(i, &splitted_var, cmd->argv) == false)
		return (false);
	expander_utils_initializer(cmd->argv, splitted_var, var_val, &utils);
	utils.dollar_index = *j;
	new_argv = garbage_malloc(sizeof(*new_argv) * (utils.len_new_argv + 1));
	while (utils.i_new < i)
		new_argv[utils.i_new++] = ft_strdup(cmd->argv[utils.i_old++]);
	manage_first_join(cmd->argv[i], new_argv, splitted_var, &utils);
	while (utils.i_split < utils.len_argv_to_append)
		new_argv[utils.i_new++] = ft_strdup(splitted_var[utils.i_split++]);
	manage_last_join(cmd->argv[i], new_argv, splitted_var, &utils);
	
	++utils.i_old;
	while (cmd->argv[utils.i_old] != 0x0)
		new_argv[utils.i_new++] = ft_strdup(cmd->argv[utils.i_old++]);
	new_argv[utils.i_new] = 0x0;
	array_free(&cmd->argv);
	array_free(&splitted_var);
	garbage_free((void **) &splitted_var);
	cmd->argv = new_argv;
	return (true);
}
