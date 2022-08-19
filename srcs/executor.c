/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/08/18 22:53:26 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Initialize AST, lex and parse [Syntax analyzer +
 * Recursive descent parser] the input read.
 * Then build AST.
 *
 * bistami task : execute AST.
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

void ft_handle_built_ins(char **args, int *error)
{
	if (ft_strcmp(args[0], "env"))
	{
		if (ft_argv_len(args) > 1)
		{
			write(2, "ERROR", 5);
			*error = 2;
		}
	}
}

void ft_handle_cmd(char **args, int *error)
{
	args[1] = args[1];
	error = error;
}

int ft_exec_cmd(t_node *node, int left)
{
	int error;

	error = 0;

	printf("ARGS\n");
	if (ft_is_built_in(node->content.simple_cmd.argv[0]))
		ft_handle_built_ins(node->content.simple_cmd.argv, &error);
	else
		ft_handle_cmd(node->content.simple_cmd.argv, &error);
	for (int i = 0; node->content.simple_cmd.argv[i]; i++)
		printf("%s %s\n", node->content.simple_cmd.argv[i], left ? "left" : "right");
	printf("\nARGS");

	if (error)
		return (2);
	else
		return (1);
}

void ft_iterate_tree(t_node *node, int left, int exec_index, char **env)
{
	if (node->type == PIPE_NODE)
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
			int pid_;

			pid_ = fork();
			if (!pid_)
			{
				dup2(fd[0], 0);
				ft_iterate_tree(node->content.child.right, 1, exec_index + 1, env);
			}
			else
			{
				if (exec_index == 0)
					wait(NULL);
				else
					exit(1);
			}
		}
	}
	else if (node->type == SIMPLE_CMD)
	{
		// int i;

		if (left == 1)
			execve(node->content.simple_cmd.argv[0], node->content.simple_cmd.argv, env);
		int pid;

		pid = fork();
		if (!pid)
		{
			execve(node->content.simple_cmd.argv[0], node->content.simple_cmd.argv, env);
		}
		else
		{
			wait(NULL);
		}

		// i = 0;
	}
	printf("\n%d\n", node->type);
}

void ft_executor(char *line, char **env)
{
	t_node *ast;

	ast = 0x0;
	if (line != 0x0)
	{
		ast = ft_lexer_parser_program(line);
		{
			if (ast != 0x0)
			{
				/*
				 * This is where you will execute the AST akhay moussa.
				 * anhayd had thrash functions.
				 */
				env = env;
				printf("\n**%d\n", ast->type);
				ft_iterate_tree(ast, 0, 0, env);
				printf("\n**%d\n", ast->type);

				// execute_ast_data(ast);
				// ast_clearing(&ast);
			}
		}
	}
}
