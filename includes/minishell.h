/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:06:31 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/07 13:29:51 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

/*
 * error defines
*/

# define ARGV_ERROR "Error : invalid argument\n"
# define WARNING "Error : outline mode\n"

/*
 * Main funnctions
*/

int		main(int argc, char **argv, char **env);
void	ft_minishell(bool inline_mode);
char	*ft_prompt(bool inline_mode);
char	*read_line(bool inline_mode);
void	ft_executor(char *line, bool inline_mode);
void	ft_add_history(char *line);
/*
 * Functions to debug states of output
*/

void	ft_print_env(char **env);

#endif
