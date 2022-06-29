/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:32:47 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/29 13:34:02 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_line(void)
{
	char	*line;

    line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("Minishell>");
	if (line)
		add_history(line);
	return (line);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main(void)
{
	char	*line;

	signal(SIGINT, sig_handler);
	line = get_line();
	printf("%s\n", line);
}
