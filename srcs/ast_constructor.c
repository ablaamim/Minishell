/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:26:22 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/04 21:22:07 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * This function is elementary in all parsers during the building of my AST,
 * it devours the next token, by freeing the first token in token_list, and
 * it sets the head to the next element in token_list.
 */

void	token_devour(t_token **token_list)
{
	t_token	*temp;

	temp = *token_list;
	if (*token_list == 0x0)
		return ;
	*token_list = (*token_list)->next;
	free(temp->data);
	free(temp);
}

/*
 * Once the lexing phase is finished, the built tokens linked list is
 * processed by the ast_constructor(), the output of the constructor will
 * be executed by the minishell loop.
 * depending on the type of token met the proper parser will be called,
 * untill the token linked list is fully scanned, or untill a closing
 * parentheses is encountered, this is because the ast_constructor()
 * will be recursively called by the parser_of_parentheses(),
 * on success ast_constructor returns true, else false.
 */
bool	ast_constructor(t_token **token_list, t_node **ast, bool is_subshell)
{
	bool	return_value;

	return_value = true;
	while (*token_list != 0x0)
	{
		if (check_logical_operators((*token_list)->type) == true)
		{
			if (*ast == 0x0)
				return (false);
			return_value = logical_operators_parser(token_list, ast,
					is_subshell);
		}
		else
			return_value = pipe_parser(token_list, ast, is_subshell);
		if (return_value == false)
			return (false);
	}
	return (true);
}

int	ft_has_wildcard(t_node *node)
{
	int	has_wild;
	int	i;

	has_wild = 0;
	i = 1;
	while (node->content.simple_cmd.argv[i])
		if (ft_strstr(node->content.simple_cmd.argv[i++], "*"))
			has_wild = 1;
	return (has_wild);
}

DIR	*ft_open_dir(char *path, char **pattern, char **clean_path)
{
	DIR	*dir;
	int	p_len;

	p_len = ft_strlen(path) - 1;
	while (path[p_len] != '/' && p_len > 0)
		p_len--;
	if (p_len < 0)
		p_len = 0;
	if (p_len > 0)
	{
		*clean_path = ft_substr(path, 0, p_len + 1);
		*pattern = ft_substr(path, p_len + 1, ((ft_strlen(path) - 1) - p_len));
	}
	else
	{
		*clean_path = ft_strdup("./");
		*pattern = path;
	}
	dir = opendir(*clean_path);
	return (dir);
}

void	ft_handle_existant_folder(struct dirent *entry,
		char *clean_pattern, char *clean_path, char **argv)
{
	char	**splited_wildcard;
	int		k;

	if ((entry->d_name[0] != clean_pattern[0]
			&& clean_pattern[0] != '*') || entry->d_name[0] == '.')
		return ;
	if (entry->d_name[ft_strlen(entry->d_name) - 1]
		!= clean_pattern[ft_strlen(clean_pattern) - 1]
		&& clean_pattern[ft_strlen(clean_pattern) - 1] != '*')
		return ;
	splited_wildcard = ft_split(clean_pattern, '*');
	k = 0;
	while (splited_wildcard[k])
	{
		if (!ft_strstr(entry->d_name, splited_wildcard[k]))
		{
			k = -10;
			break ;
		}
		free(splited_wildcard[k++]);
	}
	free(splited_wildcard);
	if (k == -10)
		return ;
	*argv = ft_strjoin(*argv, ft_strjoin(clean_path, entry->d_name, ""), "|");
}
