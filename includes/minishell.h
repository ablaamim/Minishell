/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:27:27 by ablaamim          #+#    #+#             */
/*   Updated: 2022/05/24 11:00:07 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERROR_MSG_ARG "Error : No arguments needed\n"
# define EXIT_MINISHELL "Error : Exit minishell\n"
int		main(int argc, char **argv);
void	ft_prompt(void);

#endif
