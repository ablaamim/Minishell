/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:43:55 by gruz              #+#    #+#             */
/*   Updated: 2022/09/04 20:59:49 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_handle_empty_cd(char *pwd, char *old_pwd)
{
    if (chdir(get_var("HOME")) != 0)
    {
        variadic_error_printer(2, "minishell : failed to open file\n");
        return (EXIT_FAILURE);
    }
    else // success
    {
        getcwd(pwd, sizeof(pwd));
        ft_set_env_var("PWD", pwd, 1);
        ft_set_env_var("OLDPWD", old_pwd, 1);
        return (EXIT_SUCCESS);
    }
}

int ft_handle_def_cd(char *argv, char *pwd, char *old_pwd)
{
    if (chdir(argv) != 0)
    {
        variadic_error_printer(2, "minishell : failed to open file\n");
        return (EXIT_FAILURE);
    }
    else // success
    {
        getcwd(pwd, sizeof(pwd));
        ft_set_env_var("PWD", pwd, 1);
        ft_set_env_var("OLDPWD", old_pwd, 1);
        return (EXIT_SUCCESS);
    }
}

int parse_unset(char *args)
{
    int i;

    i = 0x0;
    if (ft_isalpha(args[i]) == 0x0 && args[i] != '_')
    {
        variadic_error_printer(2, "minishell : unset '%s' not a valid identifieri\n", args);
        return (EXIT_FAILURE);
    }
    while (args[i] != '\0')
    {
        if (ft_isalnum(args[i]) == 0x0 && args[i] != '_')
        {
            variadic_error_printer(2, "minishell : unset '%s' not a valid identifier\n", args);
            return (EXIT_FAILURE);
        }
        ++i;
    }
    return (EXIT_SUCCESS);
}

/*
 * UNSET ENVIRONMENT VAR, RETURNS 1 IF IT EXISTS, AND 0 OTHERWISE.
 */

int ft_unset_logic(char *name)
{
    t_env new_env;
    int i;
    int ret;
    t_env *env;

    i = 0x0;
    env = get_bash_env();
    ret = ft_in_env(name);
    if (ret == -1)
        return (EXIT_SUCCESS);
    new_env = garbage_malloc(sizeof(char *) * env_length(*env));
    while ((*env)[i])
    {
        if (i == ret)
            garbage_free((void **)&(*env)[i]);
        else if (i >= ret)
            new_env[i - 1] = (*env)[i];
        else
            new_env[i] = (*env)[i];
        i++;
    }
    new_env[i - 1] = 0x0;
    *env = new_env;
    return (EXIT_FAILURE);
}

int ft_is_built_in(char *string)
{
    int i;
    char **built_ins;

    i = 0;
    built_ins = ft_split("env pwd echo exit cd export unset", ' ');
    while (built_ins[i])
    {
        if (built_ins[0] == 0x0 || string == 0x0)
            break;
        if (!ft_strcmp(built_ins[i], string))
            return (1);
        i++;
    }
    i = 0;
    while (built_ins[i])
        free(built_ins[i++]);
    free(built_ins);
    return (0);
}