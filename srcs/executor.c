/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:20:46 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/04 15:15:57 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void env_setter(char *name, char *val, int replace, t_env *env);

/*
 * => Unit test
 */

int ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (0x1);
	return (0x0);
}

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

int ft_argv_len(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int ft_handle_cd(char **argv)
{
	char pwd[STATIC_BYTES];
	char old_pwd[STATIC_BYTES];

	getcwd(old_pwd, sizeof(old_pwd));
	if (ft_argv_len(argv) > 2)
	{
		variadic_error_printer(2, "minishell : too many arguments\n");
		return (EXIT_FAILURE);
	}
	else if (ft_argv_len(argv) == 1 || (argv[1] && !ft_strcmp(argv[1], "~")))
	{
		if (chdir(getenv("HOME")) != 0)
		{
			variadic_error_printer(2, "minishell : failed to open file\n");
			return (EXIT_FAILURE);
		}
		else // success
		{
			getcwd(pwd, sizeof(pwd));
			ft_set_env_var("PWD", pwd, 1);
			ft_set_env_var("OLDPWD", old_pwd, 1);
		}
	}
	else if (ft_argv_len(argv) == 2)
	{
		if (chdir(argv[1]) != 0)
		{
			variadic_error_printer(2, "minishell : failed to open file\n");
			return (EXIT_FAILURE);
		}
		else // success
		{
			getcwd(pwd, sizeof(pwd));
			ft_set_env_var("PWD", pwd, 1);
			ft_set_env_var("OLDPWD", old_pwd, 1);
		}
	}
	return (EXIT_SUCCESS);
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

int ft_is_child_ignored(char *string)
{
	int i;
	char **built_ins;
	int ignored;

	i = 0;
	ignored = 0;
	built_ins = ft_split("cd unset export exit echo", ' ');
	while (built_ins[i])
	{
		if (built_ins[0] == 0x0 || string == 0x0)
			break;
		if (!ft_strcmp(built_ins[i], string))
			ignored = 1;
		i++;
	}
	i = 0;
	while (built_ins[i])
		free(built_ins[i++]);
	free(built_ins);
	return (ignored);
}

int ft_is_built_in(char *string)
{
	int i;
	char **built_ins;

	i = 0;
	built_ins = ft_split("env pwd echo exit cd export unset", ' ');
	while (built_ins[i])
	{
		if (built_ins[0] == 0x0 || string == 0x0)
			break;
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

int ft_handle_echo(char **args)
{
	int i;
	int j;
	int add_new_line;
	int k;

	i = 1;
	add_new_line = 1;
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
	return (EXIT_SUCCESS);
}

void ft_clean_argv(t_node *node)
{
	int has_wildc;
	char *new_argv;
	char *tmp;
	int i;

	has_wildc = 0;
	new_argv = ft_strdup("");
	i = 0;
	tmp = NULL;
	while (node->content.simple_cmd.argv[i])
	{
		if (ft_strchr(node->content.simple_cmd.argv[i], '*') && ft_argv_len(node->content.simple_cmd.argv) > 2)
			has_wildc = 1;
		else
		{
			tmp = ft_strdup(new_argv);
			free(new_argv);
			new_argv = ft_strjoin(tmp, node->content.simple_cmd.argv[i], "|");
			free(tmp);
		}
		i++;
	}
	if (has_wildc)
	{
		i = 0;
		while (node->content.simple_cmd.argv[i])
			free(node->content.simple_cmd.argv[i++]);
		free(node->content.simple_cmd.argv);
		// printf("newargv->%s\n", new_argv);
		node->content.simple_cmd.argv = ft_split(new_argv, '|');
		free(new_argv);
	}
}

int ft_has_wildcard(t_node *node)
{
	int has_wild;
	int i;

	has_wild = 0;
	i = 1;
	while (node->content.simple_cmd.argv[i])
		if (ft_strstr(node->content.simple_cmd.argv[i++], "*"))
			has_wild = 1;
	return (has_wild);
}

DIR *ft_open_dir(char *path, char **pattern, char **clean_path)
{
	DIR *dir;
	int p_len;

	p_len = ft_strlen(path) - 1;
	while (path[p_len] != '/' && p_len > 0)
		p_len--;
	if (p_len < 0)
		p_len = 0;
	if (p_len > 0)
	{
		*clean_path = ft_substr(path, 0, p_len + 1);
		*pattern = ft_substr(path, p_len + 1, ((ft_strlen(path) - 1) - p_len));
	}
	else
	{
		*clean_path = ft_strdup("./");
		*pattern = path;
	}
	// printf("\n-->%s\n", clean_path);
	dir = opendir(*clean_path);
	return dir;
}

void ft_handle_existant_folder(struct dirent *entry, char *clean_pattern, char *clean_path, char **argv)
{
	char **splited_wildcard;
	int k;

	splited_wildcard = NULL;
	if ((entry->d_name[0] != clean_pattern[0] && clean_pattern[0] != '*') || entry->d_name[0] == '.')
		return;
	if (entry->d_name[ft_strlen(entry->d_name) - 1] != clean_pattern[ft_strlen(clean_pattern) - 1] && clean_pattern[ft_strlen(clean_pattern) - 1] != '*')
		return;
	// printf("\npattern:%s\tpath:%s\n", clean_pattern, clean_path);
	splited_wildcard = ft_split(clean_pattern, '*');
	k = 0;
	while (splited_wildcard[k])
	{
		// printf("\n%s\n", splited_wildcard[k]);
		if (!ft_strstr(entry->d_name, splited_wildcard[k]))
		{
			k = -10;
			break;
		}
		free(splited_wildcard[k++]);
	}
	free(splited_wildcard);
	if (k == -10)
		return;
	*argv = ft_strjoin(*argv, ft_strchr(clean_path, '/') ? ft_strjoin(clean_path, entry->d_name, "") : entry->d_name, "|");
	// printf("  %s %d %s\n", entry->d_name, entry->d_type, clean_path);
}

void ft_handle_wc_extraction(t_node *node, int j, char **argv)
{
	DIR *dir;
	struct dirent *entry;
	char *clean_pattern = NULL;
	char *clean_path = NULL;

	dir = ft_open_dir(node->content.simple_cmd.argv[j], &clean_pattern, &clean_path);
	// printf("\ncleanPattern-->\t%s\nclean_path-->%s\n", clean_pattern, clean_path);
	if (dir == NULL)
		perror("opendir() error");
	else
	{
		while ((entry = readdir(dir)) != NULL)
			ft_handle_existant_folder(entry, clean_pattern, clean_path, argv);
		// printf("==>%s\n", *argv);
		free(clean_pattern);
		free(clean_path);
		closedir(dir);
	}
}

void ft_handle_wildcard(t_node *node)
{
	char *argv;
	char *tmp;
	int j;

	if (!ft_has_wildcard(node))
		return;
	argv = ft_strdup("");
	j = 0;

	while (node->content.simple_cmd.argv[j])
	{
		tmp = ft_strdup(argv);
		free(argv);
		argv = ft_strjoin(tmp, node->content.simple_cmd.argv[j++], "|");
		free(tmp);
	}
	j = 1;
	while (node->content.simple_cmd.argv[j])
	{
		ft_handle_wc_extraction(node, j, &argv);
		j++;
	}
	node->content.simple_cmd.argv = ft_split(argv, '|');
	ft_clean_argv(node);
	free(argv);
}

int ft_handle_env(char **args)
{
	int i;
	t_env *bash_env;

	i = 0x0;
	bash_env = get_bash_env();
	if (*args == 0x0)
		return (EXIT_SUCCESS);
	if (ft_argv_len(args) > 1)
	{
		variadic_error_printer(2, "env : %s %s", args[1], ENV_ERROR);
		return (127);
	}
	while ((*bash_env)[i])
	{
		if (ft_strchr((*bash_env)[i], '=') != 0x0)
		{
			printf("%s", (*bash_env)[i]);
			printf("\n");
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int ft_handle_pwd(void)
{
	char pwd[STATIC_BYTES];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		variadic_error_printer(2, "error: pwd could not be found\n");
		return (127);
	}
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}

int ft_isnumber(char *s)
{
	int i;

	i = 0x0;
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

int ft_handle_exit(char **args)
{
	int exit_status;

	exit_status = *retrieve_exit_status();
	variadic_error_printer(2, "exit\n");
	if (ft_argv_len(args) >= 2)
	{
		if (ft_isnumber(args[1]) == 0x0)
		{
			variadic_error_printer(2, "minishell : exit : %s : %s\n", NUM_ARG, args[1]);
			exit_status = 2;
		}
		else if (ft_argv_len(args) > 2)
		{
			variadic_error_printer(2, "minishell : exit : too many arguments\n");
			exit_status = 1;
		}
		else
			exit_status = ft_atoi(args[1]);
	}
	return (exit_status);
}

int export_len_name(char *argument)
{
	int len;

	len = 0x0;
	while (argument[len] != '+' && argument[len] != '=' && argument[len] != '\0')
		++len;
	return (len);
}

char *export_variable_name(char *argument)
{
	int i;
	int j;
	char *var_name;

	i = 0x0;
	j = 0x0;
	if (ft_isalpha(argument[i]) == 0x0 && argument[i] != '_')
		return (0x0);
	var_name = garbage_malloc(sizeof(*var_name) * (export_len_name(argument) + 1));
	while (argument[i] != '+' && argument[i] != '=' && argument[i] != '\0')
	{
		if (ft_isalnum(argument[i]) == 0x0)
		{
			garbage_free((void **)&var_name);
			return (0x0);
		}
		else
			var_name[j++] = argument[i];
		++i;
	}
	var_name[i] = '\0';
	if (argument[i] == '+' && argument[i + 1] != '=')
		garbage_free((void **)&var_name);
	return (var_name);
}

void export_perror(char *args, int *ret)
{
	variadic_error_printer(2, "Minishell : export : '%s' not a valid identifier\n", args);
	*ret = EXIT_FAILURE;
}

char *retrieve_var_val(char *str, char *env_val)
{
	char *var_val;

	if (*(str - 2) == '+')
		var_val = ft_strdup(env_val);
	else
		var_val = ft_strdup(str);
	return (var_val);
}

int special_env_len(t_env *env)
{
	int len = 0x0;
	while ((*env)[len])
		len++;
	return (len);
}

void append_to_env(char *export, char *var_name)
{
	bool replace;
	char *ptr;
	char *env_val;
	char *var_val;

	replace = true;
	var_val = 0x0;
	ptr = ft_strchr(export, '=');
	env_val = get_env(var_name);
	if (ptr == 0x0)
	{
		var_val = 0x0;
		if (env_val != 0x0 && env_val[-1] == '=')
			replace = false;
	}
	else
		var_val = retrieve_var_val(ptr + 1, env_val);
	if (replace == true)
		ft_set_env_var(var_name, var_val, 0x1);
	garbage_free((void **)&var_val);
}

void display_env(void)
{
	int i;
	t_env *env;

	env = get_bash_env();
	i = 0x0;
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '=') != 0x0)
			printf("declare -x %s\n", (*env)[i]);
		else
			printf("%s\n", (*env)[i]);
		i++;
	}
}

int ft_handle_export(char **args)
{
	int argc;
	int i;
	char *var_name;
	int ret;

	argc = ft_argv_len(args);
	if (argc <= 1)
		display_env();
	i = 0x1;
	ret = EXIT_SUCCESS;
	while (args[i] != 0x0)
	{
		var_name = 0x0;
		var_name = export_variable_name(args[i]);
		if (var_name == 0x0)
			export_perror(args[i], &ret);
		else
		{
			append_to_env(args[i], var_name);
			garbage_free((void **)&var_name);
		}
		++i;
	}
	return (ret);
}

int parse_unset(char *args)
{
	int i;

	i = 0x0;
	if (ft_isalpha(args[i]) == 0x0 && args[i] != '_')
	{
		variadic_error_printer(2, "minishell : unset '%s' not a valid identifieri\n", args);
		return (EXIT_FAILURE);
	}
	while (args[i] != '\0')
	{
		if (ft_isalnum(args[i]) == 0x0 && args[i] != '_')
		{
			variadic_error_printer(2, "minishell : unset '%s' not a valid identifier\n", args);
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

/*
 * UNSET ENVIRONMENT VAR, RETURNS 1 IF IT EXISTS, AND 0 OTHERWISE.
 */

int ft_unset_logic(char *name)
{
	t_env new_env;
	int i;
	int ret;
	t_env *env;

	i = 0x0;
	env = get_bash_env();
	ret = ft_in_env(name);
	if (ret == -1)
		return (EXIT_SUCCESS);
	new_env = garbage_malloc(sizeof(char *) * env_length(*env));
	while ((*env)[i])
	{
		if (i == ret)
			garbage_free((void **)&(*env)[i]);
		else if (i >= ret)
			new_env[i - 1] = (*env)[i];
		else
			new_env[i] = (*env)[i];
		i++;
	}
	new_env[i - 1] = 0x0;
	*env = new_env;
	return (EXIT_FAILURE);
}

int ft_handle_unset(char **args)
{
	int i;
	int ret;

	i = 0x0;
	ret = EXIT_SUCCESS;
	while (args[i] != 0x0)
	{
		if (parse_unset(args[i]) == EXIT_FAILURE && ret == EXIT_SUCCESS)
			ret = EXIT_FAILURE;
		ft_unset_logic(args[i]);
		++i;
	}
	return (ret);
}

int ft_handle_built_ins(char **args)
{
	int exit_stat;

	exit_stat = *retrieve_exit_status();
	if (!ft_strcmp(args[0], "export"))
		exit_stat = ft_handle_export(args);
	else if (!ft_strcmp(args[0], "unset"))
		exit_stat = ft_handle_unset(args);
	else if (!ft_strcmp(args[0], "env"))
		exit_stat = ft_handle_env(args);
	else if (!ft_strcmp(args[0], "echo"))
		exit_stat = ft_handle_echo(args);
	else if (!ft_strcmp(args[0], "pwd"))
		exit_stat = ft_handle_pwd();
	else if (!ft_strcmp(args[0], "cd"))
		exit_stat = ft_handle_cd(args);
	else if (!ft_strcmp(args[0], "exit"))
	{
		exit_stat = ft_handle_exit(args);
		exit(exit_stat);
	}
	exit_value_set(exit_stat);
	return (exit_stat);
}

int **ft_to_array(t_pipe **pipe)
{
	int i;
	t_pipe *tmp;
	int **arr;

	arr = malloc(sizeof(int *) * ft_lstsize(*pipe));
	if (!arr)
		variadic_error_printer(2, "Error : malloc() failed\n");
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

void heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_SUCCESS);
}

int ft_handle_line(char *line, t_redirs *redirs, t_node *node)
{
	line = readline(">");
	if (line == 0x0)
	{
		free(line);
		return (0x0);
	}
	if (!ft_strcmp(line, redirs->file_name))
	{
		free(line);
		return (0);
	}
	heredoc_expander(&line);
	write(node->content.simple_cmd.fd_in, line, ft_strlen(line));
	write(node->content.simple_cmd.fd_in, "\n", 1);
	free(line);
	return (1);
}

void ft_handle_heredoc(t_redirs *redirs, t_node *node)
{
	char *line;
	char *tmp;
	int pid;

	tmp = ft_strdup("/tmp/");
	line = ft_strjoin(tmp, redirs->file_name, "");
	node->content.simple_cmd.fd_in = open(line, O_RDWR | O_TRUNC | O_CREAT, 0777);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, heredoc_sig_handler);
		while (1)
		{
			if (ft_handle_line(line, redirs, node) == 0)
				break;
		}
		free(line);
		line = ft_strjoin(tmp, redirs->file_name, "");
		close(node->content.simple_cmd.fd_in);
		free(tmp);
		exit(0);
	}
	while (wait(NULL) > 0)
		write(2, "", 0);
	close(node->content.simple_cmd.fd_in);
	node->content.simple_cmd.fd_in = open(line, O_RDONLY);
	free(line);
	free(tmp);
}

void ft_handle_redirections(t_redirs *redirs, t_node *node)
{

	if (redirs == NULL)
		return;
	else if (redirs->type == INPUT_REDIR)
	{
		node->content.simple_cmd.fd_in = open(redirs->file_name, O_RDONLY);
		if (node->content.simple_cmd.fd_in == -1)
		{
			variadic_error_printer(2, "Error : file not found\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (redirs->type == OUTPUT_REDIR)
		node->content.simple_cmd.fd_out = open(redirs->file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);
	else if (redirs->type == APPEND_OUTPUT_REDIR)
		node->content.simple_cmd.fd_out = open(redirs->file_name, O_RDWR | O_APPEND | O_CREAT, 0777);
	else if (redirs->type == HEREDOC_REDIR)
		ft_handle_heredoc(redirs, node);
	ft_handle_redirections(redirs->next, node);
}

void ft_handle_dup2(t_node *node, t_pipe **pipe, int **pipes, int exec_index)
{
	if (node->content.simple_cmd.fd_in == 0)
	{
		if (exec_index - 1 >= 0)
			dup2(pipes[exec_index - 1][0], 0);
	}
	else
		dup2(node->content.simple_cmd.fd_in, 0);
	if (node->content.simple_cmd.fd_out == 1)
	{
		if (exec_index < ft_lstsize(*pipe))
			dup2(pipes[exec_index][1], 1);
	}
	else
		dup2(node->content.simple_cmd.fd_out, 1);
}

void ft_handle_child_init(t_node *node, t_pipe **pipe, int exec_index)
{
	int **pipes;

	if (node->content.simple_cmd.argv[0] && ft_is_child_ignored(node->content.simple_cmd.argv[0]))
		exit(0);
	pipes = ft_to_array(pipe);
	ft_handle_wildcard(node);
	ft_handle_dup2(node, pipe, pipes, exec_index);
	ft_close_pipes(*pipe, pipes);
	signal(SIGQUIT, signal_command_child);
	ft_free_to_array(pipe, pipes);
}

void ft_handle_child_execution(t_node *node)
{
	char *bin_path;
	char **argv;
	int ret;
	t_env *env;

	env = get_bash_env();
	if (ft_is_built_in(node->content.simple_cmd.argv[0]))
	{
		ret = ft_handle_built_ins(node->content.simple_cmd.argv);
		exit(ret);
	}
	ret = *retrieve_exit_status();
	exit_value_set(ret);
	argv = node->content.simple_cmd.argv;
	if (!argv[0])
		exit(1);
	bin_path = found_binary(argv);
	ret = manage_execution(bin_path, node->content.simple_cmd.argv[0]);
	if (ret != EXIT_SUCCESS)
	{
		exit_value_set(ret);
		exit(ret);
	}
	if (execve(bin_path, argv, *env) == ERR)
		ret = manage_execution(bin_path, node->content.simple_cmd.argv[0]);
	garbage_free((void **)&bin_path);
	exit(ret);
}

void ft_handle_child(t_node *node, t_pipe **pipe, int exec_index)
{
	ft_handle_child_init(node, pipe, exec_index);
	ft_handle_child_execution(node);
}

void ft_handle_parent(t_node *node, int pid, t_pipe **pipe)
{
	int status;

	while (waitpid(pid, &status, 0x0) > 0)
	{
		while (waitpid(-1, &status, 0x0) > 0)
			;
		write(2, "", 0);
		if (WIFEXITED(status))
		{
			exit_value_set(WEXITSTATUS(status));
			if (WEXITSTATUS(status) == 17)
				exit_value_set(0x0);
		}
	}
	if (node->content.simple_cmd.argv[0] == 0x0)
		return;
	status = *retrieve_exit_status();
	if (ft_lstsize(*pipe) == 0 && (!ft_strcmp(node->content.simple_cmd.argv[0], "exit") || !ft_strcmp(node->content.simple_cmd.argv[0], "cd") || !ft_strcmp(node->content.simple_cmd.argv[0], "export") ||
								   !ft_strcmp(node->content.simple_cmd.argv[0], "unset") || !ft_strcmp(node->content.simple_cmd.argv[0], "echo")))
	{
		status = ft_handle_built_ins(node->content.simple_cmd.argv);
		exit_value_set(status);
	}
}

void ft_handle_cmd(t_node *node, t_pipe **pipe, int *exec_index)
{
	int pid;
	int **pipes;

	pipes = NULL;
	pipes = ft_to_array(pipe);
	signal(SIGINT, signal_command);
	pid = fork();
	if (pid == ERR)
		shell_exit(EXIT_FAILURE, strerror(errno));
	if (!pid)
		ft_handle_child(node, pipe, *exec_index);
	if (*exec_index == ft_lstsize(*pipe))
	{
		ft_close_pipes(*pipe, pipes);
		ft_handle_parent(node, pid, pipe);
	}
	ft_free_to_array(pipe, pipes);
	(*exec_index)++;
}

int ft_exec_cmd(t_node *node, t_pipe **pipe, int *exec_index)
{
	int error;

	error = 0;
	ft_handle_cmd(node, pipe, exec_index);
	if (error)
		return (2);
	else
		return (1);
}

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

void ft_handle_reset(t_pipe **pipe, int *exec_index)
{
	ft_free_pipes(pipe);
	*pipe = NULL;
	*exec_index = 0;
}

void ft_iterate_tree(t_node *node, t_pipe **pipe_, int *exec_index)
{
	int fd[2];

	if (expansions_perform(node, 1) == true)
	{
		if (execute_redirections(node) == true)
		{
			if (node->type == PIPE_NODE)
			{
				if (pipe(fd) == ERR)
					shell_exit(EXIT_FAILURE, strerror(errno));
				ft_lstadd_front(pipe_, ft_lstnew(fd));
				ft_iterate_tree(node->content.child.left, pipe_, exec_index);
				ft_iterate_tree(node->content.child.right, pipe_, exec_index);
			}
			else if (node->type == SIMPLE_CMD)
				ft_exec_cmd(node, pipe_, exec_index);
			else if (node->type == OR_NODE)
			{
				ft_iterate_tree(node->content.child.left, pipe_, exec_index);
				ft_handle_reset(pipe_, exec_index);
				if (*retrieve_exit_status() != 0)
					ft_iterate_tree(node->content.child.right, pipe_, exec_index);
			}
			else if (node->type == AND_NODE)
			{
				ft_iterate_tree(node->content.child.left, pipe_, exec_index);
				ft_handle_reset(pipe_, exec_index);
				if (*retrieve_exit_status() == 0)
					ft_iterate_tree(node->content.child.right, pipe_, exec_index);
			}
			else if (node->type == SEMICO_NODE)
			{
				ft_iterate_tree(node->content.child.left, pipe_, exec_index);
				ft_handle_reset(pipe_, exec_index);
				ft_iterate_tree(node->content.child.right, pipe_, exec_index);
			}
		}
		else
			exit_value_set(EXIT_FAILURE);
	}
	else
		exit_value_set(EXIT_FAILURE);
}

void ft_init_heredoc(t_node *node, t_pipe **pipe_, int *exec_index)
{
	if (expansions_perform(node, 0) == true)
	{
		if (execute_redirections(node) == true)
		{
			if (node->type == SIMPLE_CMD)
			{
				ft_handle_redirections(node->content.simple_cmd.redirs, node);
			}
			else if (node != NULL)
			{
				ft_init_heredoc(node->content.child.left, pipe_, exec_index);
				ft_init_heredoc(node->content.child.right, pipe_, exec_index);
			}
		}
	}
}

void ft_executor(char *line)
{
	t_node *ast;
	t_pipe *pipe;
	int exec_init;

	ast = 0x0;
	pipe = NULL;
	exec_init = 0;
	if (line != 0x0)
	{
		ast = ft_lexer_parser_program(line);
		{

			if (ast != 0x0)
			{
				ft_init_heredoc(ast, &pipe, &exec_init);
				ft_iterate_tree(ast, &pipe, &exec_init);
				ft_free_pipes(&pipe);
				ast_clearing(&ast);
			}
		}
	}
}
