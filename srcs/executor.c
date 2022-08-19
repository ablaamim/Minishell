/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/19 21:41:07 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Initialize AST, lex and parse [Syntax analyzer +
 * Recursive descent parser] the input read.
 * Then build AST.
 *
 * bistami task : execute AST
 * -> pipes : DONE
 * -> simple_cmd works with absolute path : DONE
 * -> simple_cmd relative path : DONE
 *
 * TO  DO : builtins
 *
 * ablaamim to do : Init env for execve : DONE !
 * ablaamim to do : Perform expansion.
 *
 * EXPANDER : remove quotes from input : DONE !
 * EXPANDER : expand var : in progress.
 *
 * --> 0 LEAKS TILL NOW.
 *
 */

int ft_is_built_in(char *string)
{
	int i;
	char **built_ins;

	i = 0;
	built_ins = ft_split("env pwd echo", ' ');
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
 * Built-in manager.
 * built_in env works like a chrm now.
 */

void ft_handle_built_ins(char **args, char **env, int *error)
{
	if (!ft_strcmp(args[0], "env"))
	{
		if (ft_argv_len(args) > 1)
		{
			variadic_error_printer(2, "env : %s %s", args[1], ENV_ERROR);
			*error = 2;
		}
		else
			ft_print_env(env);
	}
	else if (!ft_strcmp(args[0], "echo"))
		ft_handle_echo(args);
}

void ft_handle_cmd(t_node *node, int htf, char **env, int *error)
{
	int pid;
	char *bin_path;
	char **argv;

	//(void) *error;
	//(void) htf;
	argv = node->content.simple_cmd.argv;
	bin_path = found_binary(argv);
	if (htf == 1)
	{
		// execve(node->content.simple_cmd.argv[0], node->content.simple_cmd.argv, env);
		execve(bin_path, argv, env);
	}
	pid = fork();
	if (!pid)
	{
		*error = execve(bin_path, argv, env);
		//*error = execve(node->content.simple_cmd.argv[0], node->content.simple_cmd.argv, env);
	}
	else
		wait(0x0);
}

int ft_exec_cmd(t_node *node, int htf, char **env)
{
	int error;

	error = 0;
	// printf("ARGS\n");
	if (ft_is_built_in(node->content.simple_cmd.argv[0]))
		ft_handle_built_ins(node->content.simple_cmd.argv, env, &error);
	else
		ft_handle_cmd(node, htf, env, &error);
	/*
	for (int i = 0; node->content.simple_cmd.argv[i]; i++)
		printf("%s %s\n", node->content.simple_cmd.argv[i], htf ? "left" : "right");
	printf("\nARGS");
	*/
	if (error)
		return (2);
	else
		return (1);
}

int ft_handle_pipe_extanded(t_node *node, int exec_index, char **env, int fd)
{
	int pid_;

	pid_ = fork();
	if (!pid_)
	{
		dup2(fd, 0);
		ft_iterate_tree(node->content.child.right, 1, exec_index + 1, env);
	}
	else
	{
		if (exec_index == 0)
			wait(NULL);
		else
			exit(1);
	}
	return (0);
}

int ft_handle_pipe(t_node *node, int exec_index, char **env)
{
	int pid;
	int fd[2];

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_iterate_tree(node->content.child.left, 1, exec_index + 1, env);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		ft_handle_pipe_extanded(node, exec_index, env, fd[0]);
	}
	return (0);
}

void ft_iterate_tree(t_node *node, int has_to_fork, int exec_index, char **env)
{
	if (expansions_perform(node) == true) // See expansions_performer.c // expansion ana li andirha so dw
	{
		/*
		 * Labghiti tkhdemhum recursively hahya function w data raha organized in simple_cmd
		 */
		/*if (execute_redirections(node) == true) // See exec_redirections.c
		{
		*/
		if (node->type == PIPE_NODE)
			ft_handle_pipe(node, exec_index, env);
		else if (node->type == SIMPLE_CMD)
			ft_exec_cmd(node, has_to_fork, env);

		/*
		}
		else
			exit_value_set(EXIT_FAILURE);
	*/
	}
	else
		exit_value_set(EXIT_FAILURE); // see exit_shell.c its static int set on 0x0 and gets updated after every call.
}

/*
 * -> Cache env is ready now !
 */

void ft_executor(char *line, char **env)
{
	t_node *ast;
	t_env *bash_env;

	ast = 0x0;
	bash_env = get_bash_env();
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
				ft_iterate_tree(ast, 0, 0, *bash_env);
				// printf("\n**%d\n", ast->type);

				// execute_ast_data(ast);
				// ast_clearing(&ast);
			}
		}
	}
}
