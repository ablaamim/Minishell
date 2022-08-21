/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/20 20:09:57 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Leak_Hunter/leak_hunter.h"

/*
 * Initialize AST, lex and parse [Syntax analyzer +
 * Recursive descent parser] the input read.
 * Then build AST.
 *
 * bistami task : execute AST
 * -> pipes : Fix remaining errors
 *
 * TO  DO : export, unset, get appropriate exit status.
 *          heredoc
 *
 * work together on redirections.
 *
 * ablaamim tasks :
 * EXPANDER : remove quotes from input : DONE !
 * EXPANDER : perform expansions : DONE.
 * LOGICAL OPERATOR AND : DONE.
 * LOGICAL OPERATOR OR : DONE.
 * LOGICALGICAL OPERATOR SIMICO : DONE.
 * WILDCARD.
 *
 * --> LEAKS REMAINING WHEN EXPANSION IS PERFORMED.
 *
 *  REVIEWED : exit, env, pwd : works so well now.
 *
 * TO DO : REVIEW ECHO
 *
 */

int ft_lstsize(t_pipe *lst)
{
	int counter;

	counter = 0;
	while (lst != NULL)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}
t_pipe *ft_lstlast(t_pipe *lst)
{
	if (ft_lstsize(lst) == 0)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
void ft_lstadd_front(t_pipe **head, t_pipe *new)
{
	new->next = *(head);
	*(head) = new;
}
t_pipe *ft_lstnew(int *fd)
{
	t_pipe *lst;

	lst = (t_pipe *)malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->fd[0] = fd[0];
	lst->fd[1] = fd[1];
	lst->next = NULL;
	return (lst);
}
void ft_lstadd_back(t_pipe **alst, t_pipe *new)
{
	t_pipe *last;

	if (new != NULL)
	{
		if (ft_lstsize(*(alst)) > 0)
		{
			last = ft_lstlast(*(alst));
			last->next = new;
		}
		else
			ft_lstadd_front(alst, new);
	}
}

int ft_is_built_in(char *string)
{
	int i;
	char **built_ins;

	i = 0;
	built_ins = ft_split("env pwd echo exit", ' ');
	while (built_ins[i])
	{
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

int ft_argv_len(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void ft_echo_iterator(char **args, int *k, int i)
{
	*k = 1;
	while (args[i][*k] == 'n')
		(*k)++;
}

void ft_echo_print(char **args, int i, int j, int add_new_line)
{
	while (args[i])
	{
		printf("%s", args[i++]);
		if (i < j)
			printf(" ");
	}
	if (add_new_line)
		printf("\n");
}

void ft_handle_echo(char **args)
{
	int i;
	int j;
	int add_new_line = 1;
	int k;

	i = 1;
	j = ft_argv_len(args);
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		ft_echo_iterator(args, &k, i);
		if ((size_t)k < ft_strlen(args[i]))
			break;
		add_new_line = 0;
		i++;
	}
	ft_echo_print(args, i, j, add_new_line);
}

/*
 * env builtin improved.
 */

void ft_handle_env(char **args, char **env, int *error)
{
	int i;

	i = 0x0;
	if (ft_argv_len(args) > 1)
	{
		variadic_error_printer(2, "env : %s %s", args[1], ENV_ERROR);
		*error = 2;
	}
	while (env[i])
	{
		if (ft_strchr(env[i], '=') != 0x0)
		{
			printf("%s", env[i]);
			printf("\n");
		}
		i++;
	}
}

void ft_handle_pwd(void)
{
	char pwd[256000];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		variadic_error_printer(2, "ERROR: PWD COULD NOT BE FOUND\n", ENV_ERROR);
		return;
	}
	printf("%s\n", pwd);
}

int ft_isnumber(char *s)
{
	int i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void ft_handle_exit(char **args)
{
	int exit_status;

	// exit_status = 0;
	exit_status = *retrieve_exit_status();
	// printf("exit\n");
	variadic_error_printer(2, "exit\n");
	if (ft_argv_len(args) >= 2)
	{
		if (ft_isnumber(args[1]) == 0x0)
		{
			// exit_status = ft_atoi_(args[1]) % 256;
			// if ((exit_status == 0 && ft_strcmp(args[1], "0") && ft_atoi_(args[1]) == 256))
			//{
			variadic_error_printer(2, "minishell : exit : %s : %s\n", NUM_ARG, args[1]);
			exit_status = 2; // TODO REPLACE EXIT STATUS WITH MACOS EXIT STATUS [256] // DONE
							 //}
		}
		else if (ft_argv_len(args) > 2)
		{
			variadic_error_printer(2, "minishell : exit : too many arguments\n");
			exit_status = 1;
		}
		else
			exit_status = ft_atoi(args[1]);
	}
	exit(exit_status);
}

/*
 * Built-in manager.
 * built_in env works like a chrm now.
 */

void ft_handle_built_ins(char **args, char **env, int *error)
{
	if (!ft_strcmp(args[0], "env"))
		ft_handle_env(args, env, error);
	else if (!ft_strcmp(args[0], "echo"))
		ft_handle_echo(args);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_handle_pwd();
	else if (!ft_strcmp(args[0], "exit"))
		ft_handle_exit(args);
}

int **ft_to_array(t_pipe **pipe)
{
	int i;
	t_pipe *tmp;
	int **arr;

	arr = malloc(sizeof(int *) * ft_lstsize(*pipe));
	i = 0;
	while (i < ft_lstsize(*pipe))
		arr[i++] = malloc(sizeof(int) * 2);
	i = 0;
	tmp = *pipe;
	while (tmp)
	{
		arr[i][0] = tmp->fd[0];
		arr[i][1] = tmp->fd[1];
		tmp = tmp->next;
		i++;
	}
	return (arr);
}

void ft_free_to_array(t_pipe **pipe, int **arr)
{
	int i;

	i = 0;
	while (i < ft_lstsize(*pipe))
		free(arr[i++]);
	free(arr);
}

void ft_close_pipes(t_pipe *pipe, int **arr)
{
	int i;
	int j;

	i = 0;
	while (i < ft_lstsize(pipe))
	{
		j = 0;
		while (j < 2)
			close(arr[i][j++]);
		i++;
	}
}

void ft_handle_child(t_node *node, t_pipe **pipe, int exec_index, char **env)
{
	char *bin_path;
	char **argv;
	int ret;
	int **pipes;

	argv = node->content.simple_cmd.argv;
	bin_path = found_binary(argv);
	pipes = ft_to_array(pipe);
	if (exec_index - 1 >= 0)
		dup2(pipes[exec_index - 1][0], 0);
	if (exec_index < ft_lstsize(*pipe))
		dup2(pipes[exec_index][1], 1);
	ft_close_pipes(*pipe, pipes);
	ret = manage_execution(bin_path, node->content.simple_cmd.argv[0]);
	if (ret != EXIT_SUCCESS)
		exit(ret);
	execve(bin_path, argv, env);
	ret = manage_execution(bin_path, node->content.simple_cmd.argv[0]);
	if (ret != EXIT_SUCCESS)
		exit(ret);
}

void ft_handle_cmd(t_node *node, t_pipe **pipe, int *exec_index, char **env)
{
	int pid;

	int **pipes;

	pipes = NULL;
	pipes = ft_to_array(pipe);
	pid = fork();
	if (!pid)
	{
		ft_handle_child(node, pipe, *exec_index, env);
		//*error = execve(node->content.simple_cmd.argv[0], node->content.simple_cmd.argv, env);
	}
	if (*exec_index == ft_lstsize(*pipe))
	{
		ft_close_pipes(*pipe, pipes);
		while (wait(NULL) > 0)
			write(2, "", 0);
	}
	ft_free_to_array(pipe, pipes);
	(*exec_index)++;
}

int ft_exec_cmd(t_node *node, t_pipe **pipe, int *exec_index, char **env)
{
	int error;

	error = 0;
	if (ft_is_built_in(node->content.simple_cmd.argv[0]))
	{
		ft_handle_built_ins(node->content.simple_cmd.argv, env, &error);
	}
	else
		ft_handle_cmd(node, pipe, exec_index, env);

	if (error)
		return (2);
	else
		return (1);
}

void ft_iterate_tree(t_node *node, t_pipe **pipe_, int *exec_index, char **env)
{
	int fd[2];
	if (expansions_perform(node) == true) // See expansions_performer.c // expansion ana li andirha so dw
	{
		if (node->type == PIPE_NODE)
		{
			pipe(fd);
			ft_lstadd_front(pipe_, ft_lstnew(fd));
			ft_iterate_tree(node->content.child.left, pipe_, exec_index, env);
			ft_iterate_tree(node->content.child.right, pipe_, exec_index, env);
		}
		else if (node->type == SIMPLE_CMD)
			ft_exec_cmd(node, pipe_, exec_index, env);
		else
			execute_command_list(node); // LOGICAL OPERATORS BONUS
										/*
										}
										else
											exit_value_set(EXIT_FAILURE);
									*/
	}
	else
		exit_value_set(EXIT_FAILURE);
}

/*
 * -> Cache env is ready now !
 */
void ft_free_pipes(t_pipe **pipe)
{
	t_pipe *p;
	t_pipe *tmp;

	p = *pipe;
	while (p)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

void ft_executor(char *line, char **env)
{
	t_node *ast;
	t_env *bash_env;
	t_pipe *pipe;
	int exec_init;

	ast = 0x0;
	bash_env = get_bash_env();
	pipe = NULL;
	exec_init = 0;
	(void)env;
	// printf("======================= MINI HELL CACHE =======================\n");
	// ft_print_env(*bash_env);
	if (line != 0x0)
	{
		ast = ft_lexer_parser_program(line);
		{
			if (ast != 0x0)
			{
				// env = env;
				// printf("\n**%d\n", ast->type);
				ft_iterate_tree(ast, &pipe, &exec_init, *bash_env);
				ft_free_pipes(&pipe);
				atexit(leak_report);
				// execute_ast_data(ast);
				// ast_clearing(&ast);
			}
		}
	}
}
