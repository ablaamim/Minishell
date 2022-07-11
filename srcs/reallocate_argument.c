/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocate_argument.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:25:40 by ablaamim          #+#    #+#             */
/*   Updated: 2022/07/10 20:42:09 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_first_join(
		char *arg, char **new_argv, char **splitted_var, t_expand_utils *utils)
{
	char	*before_dollar;

	before_dollar = ft_strndup(arg, utils->index_dollar);
	if (utils->first_join == true)
	{
		new_argv[utils->i_new]
			= ft_strjoin(before_dollar, splitted_var[utils->i_split], "");
		++utils->i_new;
		++utils->i_split;
		free(before_dollar);
	}
	else if (*before_dollar != '\0')
	{
		new_argv[utils->i_new] = before_dollar;
		++utils->i_new;
	}
	else
		free(before_dollar);
}

void	init_expand_utils(char **argv, char **splitted_var, char *var_value,
		t_expand_utils *utils)
{
	utils->has_space = has_a_space(var_value);
	utils->first_join = (ft_isspace(var_value[0]) == 0);
	utils->last_join = (ft_isspace(var_value[ft_strlen(var_value) - 1]) == 0);
	utils->len_old_argv = retrieve_len_array(argv);
	utils->len_argv_to_add = retrieve_len_array(splitted_var);
	utils->len_new_argv = utils->len_old_argv + utils->len_argv_to_add
		- (utils->first_join == false) - (utils->last_join == false)
		+ (utils->has_space == true);
	utils->i_old = 0;
	utils->i_new = 0;
	utils->i_split = 0;
}

void	handle_last_join(
		char *arg, char **new_argv, char **splitted_var, t_expand_utils *utils)
{
	char	*after_var;

	after_var = get_after_var(arg, utils->index_dollar);
	if (utils->last_join == true && *after_var != '\0')
	{
		free((void **)&new_argv[utils->i_new - 1]);
		new_argv[utils->i_new - 1]
			= ft_strjoin(splitted_var[utils->i_split - 1], after_var, "");
		++utils->i_split;
	}
	else if (*after_var != '\0')
		new_argv[utils->i_new++] = ft_strdup(after_var);
}

bool	check_if_expansion_is_valid(int i, char ***splitted_var, char **argv)
{
	if (i > 0 && retrieve_len_array(*splitted_var) > 1
		&& arg_content_is_redirected(argv[i - 1]) == true)
	{
		variadic_error_printer(STDERR_FILENO,
			"minishell: %s: ambiguous redirect\n", argv[i]);
		free(splitted_var);
		return (false);
	}
	return (true);
}

bool	reallocate_argument(
		t_simple_cmd *cmd, int const i, int *j, char *var_value)
{
	t_expand_utils	utils;
	char			**new_argv;
	char			**splitted_var;

	splitted_var = ft_split(var_value, ' ');
	if (check_if_expansion_is_valid(i, &splitted_var, cmd->argv) == false)
		return (false);
	init_expand_utils(cmd->argv, splitted_var, var_value, &utils);
	utils.index_dollar = *j;
	new_argv = malloc(sizeof(*new_argv) * (utils.len_new_argv + 1));
	while (utils.i_new < i)
		new_argv[utils.i_new++] = ft_strdup(cmd->argv[utils.i_old++]);
	handle_first_join(cmd->argv[i], new_argv, splitted_var, &utils);
	while (utils.i_split < utils.len_argv_to_add)
		new_argv[utils.i_new++] = ft_strdup(splitted_var[utils.i_split++]);
	handle_last_join(cmd->argv[i], new_argv, splitted_var, &utils);
	++utils.i_old;
	while (cmd->argv[utils.i_old] != NULL)
		new_argv[utils.i_new++] = ft_strdup(cmd->argv[utils.i_old++]);
	new_argv[utils.i_new] = NULL;
	ft_free_array(&cmd->argv);
	ft_free_array(&splitted_var);
	free(splitted_var);
	cmd->argv = new_argv;
	return (true);
}

