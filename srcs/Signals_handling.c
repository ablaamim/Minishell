#include "../includes/minishell.h"

void	ft_wait_4_sig(int sig, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&(sa.sa_mask));
	sigaddset(&(sa.sa_mask), sig);
	if (sigaction(sig, &sa, NULL))
	{
		perror(strerror(sig));
		exit(EXIT_FAILURE);
	}
}

void	ft_ignore_signal(int signal)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&(sa.sa_mask));
	sigaddset(&(sa.sa_mask), signal);
	if (sigaction(signal, &sa, NULL))
	{
		perror(strerror(signal));
		exit(EXIT_FAILURE);
	}
}

void	handling_sigquit(int signal)
{
	char	**env;
	char	*nb_cmd;

	(void)signal;
	env = ft_read_env(ENV_FILE);
	if (!env)
		return ;
	nb_cmd = ft_getenv_arr("?nb_cmd", env);
	if (!ft_strcmp(nb_cmd, "1"))
		ft_putendl_fd("Quit: 3", 2);
	free(nb_cmd);
	free_char_array(env);
}

void	handling_sigint(int signal, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	(void)signal;
	ft_putendl("");
}

void	toggle_signals(int toggle)
{
	if (toggle)
	{
		ft_wait_4_sig(SIGINT, handling_sigint);
		ft_wait_4_sig(SIGQUIT, ft_receive_sig);
	}
	else
	{
		ft_wait_4_sig(SIGINT, ft_receive_sig);
		ft_ignore_signal(SIGQUIT);
	}
	ft_init_terminal(toggle);
}
