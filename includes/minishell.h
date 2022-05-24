/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:02:16 by ablaamim          #+#    #+#             */
/*   Updated: 2022/05/24 02:00:35 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <assert.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
 * Definition of type codes
*/

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5
# define MAX_ARGS 10

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_exec_cmd
{
	int		type;
	char	*argv[MAX_ARGS];
	char	*eargv[MAX_ARGS];
}	t_exec_cmd;

typedef struct s_redir_cmd
{
	int		type;
	t_cmd	cmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}	t_redir_cmd;

typedef struct s_pipe_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe_cmd;

typedef struct s_list_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_list_cmd;

typedef	struct s_back_cmd
{
	int		type;
	t_cmd	*cmd;
}	t_back_cmd;

/*
 * Constructors
*/

int	main(int argc, char **argv);
int	get_cmd(char *buff, int nbuff);

#endif
