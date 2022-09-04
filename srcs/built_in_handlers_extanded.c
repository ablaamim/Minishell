/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_handlers_extanded.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:48:49 by gruz              #+#    #+#             */
/*   Updated: 2022/09/04 21:24:45 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_handle_unset(char **args)
{
    int i;
    int ret;

    i = 0x0;
    ret = EXIT_SUCCESS;
    while (args[i] != 0x0)
    {
        if (parse_unset(args[i]) == EXIT_FAILURE && ret == EXIT_SUCCESS)
            ret = EXIT_FAILURE;
        ft_unset_logic(args[i]);
        ++i;
    }
    return (ret);
}

int ft_handle_echo(char **args)
{
    int i;
    int j;
    int add_new_line;
    int k;

    i = 1;
    add_new_line = 1;
    j = ft_argv_len(args);
    while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
    {
        ft_echo_iterator(args, &k, i);
        if ((size_t)k < ft_strlen(args[i]))
            break;
        add_new_line = 0;
        i++;
    }
    ft_echo_print(args, i, j, add_new_line);
    return (EXIT_SUCCESS);
}

void	ft_handle_wc_extraction(t_node *node, int j, char **argv)
{
	DIR		*dir;
	struct	dirent *entry;
	char	*clean_pattern = NULL;
	char	*clean_path = NULL;

	dir = ft_open_dir(node->content.simple_cmd.argv[j], &clean_pattern, &clean_path);
	if (dir == NULL)
		perror("opendir() error");
	else
	{
		entry = readdir(dir);
		while (entry != NULL)
		{
			ft_handle_existant_folder(entry, clean_pattern, clean_path, argv);
			entry = readdir(dir);
		}
		free(clean_pattern);
		free(clean_path);
		closedir(dir);
	}
}

void	ft_handle_wildcard(t_node *node)
{
	char	*argv;
	char	*tmp;
	int		j;

	if (!ft_has_wildcard(node))
		return ;
	argv = ft_strdup("");
	j = 0;
	while (node->content.simple_cmd.argv[j])
	{
		tmp = ft_strdup(argv);
		free(argv);
		argv = ft_strjoin(tmp, node->content.simple_cmd.argv[j++], "|");
		free(tmp);
	}
	j = 1;
	while (node->content.simple_cmd.argv[j])
	{
		ft_handle_wc_extraction(node, j, &argv);
		j++;
	}
	node->content.simple_cmd.argv = ft_split(argv, '|');
	ft_clean_argv(node);
	free(argv);
}