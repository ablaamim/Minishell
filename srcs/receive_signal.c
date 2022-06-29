#include "../include/minishell.h"

void	ft_receive_sig(int signal, siginfo_t *info, void *ctx)
{
	(void)ctx;
	(void)info;
	if (signal == SIGINT)
	{
		set_exitstatus(1);
		ft_putendl("");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		handling_sigquit(signal);
}
