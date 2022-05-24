/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:27:27 by ablaamim          #+#    #+#             */
/*   Updated: 2022/05/24 19:27:33 by ablaamim         ###   ########.fr       */
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

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5

# define MAX_ARGS 256

typedef struct s_cmd
{
	int	type_code;
}	t_cmd;

typedef struct s_execcmd
{
	int		type_code;
	char	*argv[MAX_ARGS];
	char	*eargv[MAX_ARGS];
}	t_execcmd;

typedef struct s_redircmd
{
	int		type_code;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}	t_redircmd;

typedef struct s_pipecmd
{
	int		type_code;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_listcmd
{
	int		type_code;
	t_cmd	*left;
	t_cmd	*right;
}	t_listcmd;

typedef struct s_backcmd
{
	int		type_code;
	t_cmd	*cmd;
}	t_backcmd;


int		main(int argc, char **argv);
void	ft_close_file_descriptors(void);
void	ft_prompt(void);
int		read_input_buffer(void);
void	ft_save_history(char *input);

/*
 * Libft utils
*/

void	*ft_memset(void *s, int c, size_t n);

#endif
