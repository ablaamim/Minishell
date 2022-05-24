/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:04:00 by ablaamim          #+#    #+#             */
/*   Updated: 2022/05/24 02:17:57 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

int	get_cmd(char *buff, int nbuff)
{
	ft_memset(buff, 0x0, nbuff);
	//buff = readline("minishell$>");
	fgets(buff, nbuff, stdin);
	buff = readline("\e[30;47;3m minishell > \e[0m ");
	if (buff[0] == 0x0) // END OF FILE
		return (-1);
	add_history(buff);
	return (EXIT_SUCCESS);
}
void	ft_panic(char *s)
{
	write(2, s, sizeof(s));
	exit(EXIT_FAILURE);
}
int	fork1(void)
{
	int	pid;
	pid = fork();
	if (pid == -1)
		ft_panic("Fork failed\n");
	return (pid);
}
*/
/*
void	run_cmd(t_cmd *cmd)
{
	int			p[2];
	t_back_cmd	*bcmd;
	t_exec_cmd	*ecmd;
	t_list_cmd	*lcmd;
	t_pipe_cmd	*pcmd;
	t_redir_cmd	*rcmd;

	if (cmd == 0x0)
		exit (EXIT_FAILURE);
	if (cmd->type == EXEC)
	{
		ecmd = (t_exec_cmd *) cmd;
		if(ecmd->argv[0] == 0)
			exit();
	}
	else
	{
		fprintf(stderr, "unknown runcmd\n");
		exit(-1);
	}
}
*/

int	ft_read_input(void)
{
	char	*input;
	t_cmd	*cmd;
	int		ret;

	ret = 1;
	cmd = NULL;
	input = readline("\e[30;47;3m minishell > \e[0m ");
	if (!input)
		return (0);
	if (!strlen(input))
		return (0x1);
	add_history(input);
	return (ret);
}

int	ft_prompt(void)
{
	int	ret;

	ret = 0;
	while (1)
	{
		ret = ft_read_input();
		if (!ret)
			write(2, "\e[A\e[14Cexit", sizeof("\e[A\e[14Cexit"));
		else if (ret == -1)
			write(2, "minishell: syntax error", sizeof("minishell: syntax error"));
	}
	return (1);
}

int	main(int argc, char **argv)
{
	//static char	buff[256];
	//int			fd;

	if (argc == 1)
	{
		/*
		fd = open("console", O_RDWR);
		while (fd >= 0)
		{
			if (fd >= 3)
				close(fd);
			break;
		}
		while (get_cmd(buff, sizeof(buff)) >= 0)
		{
			if(buff[0] == 'c' && buff[1] == 'd' && buff[2] == ' ')
			{
				buff[strlen(buff) - 1] = 0;
				if(chdir(buff + 3) < 0)
					fprintf(stderr, "cannot cd %s\n", buff + 3);
				continue;
			}
			if (fork1 == 0)
				run_cmd(parse_cmd(buff));
			wait(0);
			
		}
		*/
		ft_prompt();
	}
	else
		write(2, "No args required\n", 6);
	exit(EXIT_SUCCESS);
}
