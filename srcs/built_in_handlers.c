/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:40:25 by gruz              #+#    #+#             */
/*   Updated: 2022/09/04 22:20:21 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_handle_cd(char **argv)
{
    char old_pwd[STATIC_BYTES];

    getcwd(old_pwd, sizeof(old_pwd));
    if (ft_argv_len(argv) > 2)
    {
        variadic_error_printer(2, "minishell : too many arguments\n");
        return (EXIT_FAILURE);
    }
    else if (ft_argv_len(argv) == 1 || (argv[1] && !ft_strcmp(argv[1], "~")))
    {
        return (ft_handle_empty_cd(old_pwd));
    }
    else if (ft_argv_len(argv) == 2)
    {
        return (ft_handle_def_cd(argv[1], old_pwd));
    }
    return (EXIT_SUCCESS);
}

int ft_handle_env(char **args, t_node *node)
{
    int i;
    t_env *bash_env;

    i = 0x0;
    bash_env = get_bash_env();
    if (*args == 0x0)
        return (EXIT_SUCCESS);
    if (ft_argv_len(args) > 1)
    {
        variadic_error_printer(2, "env : %s %s", args[1], ENV_ERROR);
        return (127);
    }
    while ((*bash_env)[i])
    {
        if (ft_strchr((*bash_env)[i], '=') != 0x0)
        {
            variadic_error_printer(node->content.simple_cmd.fd_out, "%s", (*bash_env)[i]);
            variadic_error_printer(node->content.simple_cmd.fd_out, "\n");

        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int ft_handle_pwd( t_node *node)
{
    char pwd[STATIC_BYTES];

    if (getcwd(pwd, sizeof(pwd)) == NULL)
    {
        variadic_error_printer(2, "error: pwd could not be found\n");
        return (127);
    }
    variadic_error_printer(node->content.simple_cmd.fd_out,"%s\n", pwd);
    return (EXIT_SUCCESS);
}

int ft_handle_exit(char **args, t_node *node)
{
    int exit_status;

    exit_status = *retrieve_exit_status();
    variadic_error_printer(node->content.simple_cmd.fd_out, "exit\n");
    if (ft_argv_len(args) >= 2)
    {
        if (ft_isnumber(args[1]) == 0x0)
        {
            variadic_error_printer(2, "minishell : exit : %s : %s\n", NUM_ARG, args[1]);
            exit_status = 2;
        }
        else if (ft_argv_len(args) > 2)
        {
            variadic_error_printer(2, "minishell : exit : too many arguments\n");
            exit_status = 1;
        }
        else
            exit_status = ft_atoi(args[1]);
    }
    return (exit_status);
}

int ft_handle_export(char **args, t_node *node)
{
    int argc;
    int i;
    char *var_name;
    int ret;

    argc = ft_argv_len(args);
    if (argc <= 1)
        display_env(node);
    i = 0x1;
    ret = EXIT_SUCCESS;
    while (args[i] != 0x0)
    {
        var_name = 0x0;
        var_name = export_variable_name(args[i]);
        if (var_name == 0x0)
            export_perror(args[i], &ret);
        else
        {
            append_to_env(args[i], var_name);
            garbage_free((void **)&var_name);
        }
        ++i;
    }
    return (ret);
}