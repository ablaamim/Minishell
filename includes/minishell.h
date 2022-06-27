/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:06:31 by ablaamim          #+#    #+#             */
/*   Updated: 2022/06/27 15:57:52 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <stdarg.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>

/*
 * Error defines, i display them in stderr using write() with fd == 2.
 * ===> Useless eight now, i will delete then later.
 * [WARNING !!! ALL ERROR DEFINES WILL BE USELESS!!!!!!!!!!!!!!!!!!!!!!!]
 * [SOLUTION : VARIADIC_ERROR_PRINTER() FUNCTIONALITY.]
*/

# define ARGV_ERROR "Error : invalid argument\n"
# define WARNING "Error : outline mode\n"
# define MALLOC_ERROR "Error : malloc() failed to allocate memory\n"
# define ERROR_MINISHELL_EOF "minishell : syntax error, unexpected eof\n"
# define ERROR_AND "Minishell : the '&' is not handled by program\n"
# define ERROR_TOKEN "Error : syntax error near unexpected token\n"
# define SIZEOF_ONE_CHAR_STRING 2
# define SIZEOF_TWO_CHAR_STRING 3
# define SYNTAX_ERROR_EXIT 2
/*
 * LEXER ABSTRACTION.
*/

/*
 * Must contain all char types, during the lexing phase the proper
 * Tokenizer will be called accordingly to the type encountred whle scanning
 * input read by readline(), and apply Lexing rules.
*/

enum e_char_type
{
	ANY_CHAR,
	NULL_CHAR,
	SPACE_CHAR,
	SQUOTE_CHAR,
	DQUOTE_CHAR,
	LESS_CHAR,
	GREAT_CHAR,
	AND_CHAR,
	SEMICO_CHAR,
	PIPE_CHAR,
	OP_PARENTH_CHAR,
	CLOSE_PARENTH_CHAR,
	NB_CHAR_TYPE
};

/*
 * All types of tokens handled by the prgram, this will simplify parsing.
*/

enum e_token_type
{
	WORD_TOKEN,
	PIPE_TOKEN,
	OR_TOKEN,
	AND_TOKEN,
	SEMICO_TOKEN,
	LESSER_TOKEN,
	DLESSER_TOKEN,
	GREATER_TOKEN,
	DGREATER_TOKEN,
	AMPERSAND_TOKEN,
	OP_PARENTH_TOKEN,
	CLOSE_PARENTH_TOKEN
};

/*
 * Word token rules, its either accepted or not_accepted.
*/

enum e_char_rules
{
	NOT_ACCEPTED,
	ACCEPTED
};

/*
 * Finally we need a tokens linked list to reperesent data in memory, also
 * debug it in order to test.
*/

typedef struct s_token
{
	char				*data;
	enum e_token_type	type;
	struct s_token		*next;
}	t_token;

/*
 * PARSER ABSTRACTION
*/

/*
 * All code types of nodes that can be found in my AST,
 * leaves are considered as nodes too.
*/

enum e_node_type
{
	SIMPLE_CMD,
	PIPE_NODE,
	OR_NODE,
	AND_NODE,
	SEMICO_NODE
};

/*
 * All possible types of redirection that we can encounter in a simple
 * command, I/O - Append - Heredoc
*/

enum e_redirection_type
{
	INPUT_REDIR,
	HEREDOC_REDIR,
	OUTPUT_REDIR,
	APPEND_OUTPUT_REDIR,
	NO_REDIR
};

/*
 * Simple command, it can be composed of options (arguments), i/o stream
 * and quotes (single / double).
*/

typedef struct s_simple_cmd
{
	char	**argv;
	int		fd_in;
	int		fd_out;
	bool	input_has_quotes;
}	t_simple_cmd;

/*
 * A node in our AST, it always has children, one on the left,
 * and one on the right.
*/

typedef struct s_child
{
	struct s_node	*left;
	struct s_node	*right;
}	t_child;

/*
 * A member of the AST that contains a node_type and a content,
 * which can be a simple command or a child.
 * - If content is a simple_cmd the type is 1.
 * - If content is a pipe, the type will be 2.
 * [Union didnt work well] So im using a simple struct now.
*/

typedef struct s_node_content
{
	int					type;
	struct s_simple_cmd	simple_cmd;
	struct s_child		child;
}	t_node_content;

/*
 * A member of the AST (node) contains a node_type and a content which can
 * be a simple command or a child.
*/

typedef struct s_node
{
	enum e_node_type	type;
	t_node_content		content;
}	t_node;

/*
 * Garbage memory collection data struct, it is a linked list.
*/

typedef struct s_garbage_list
{
	void					*ptr;
	struct s_garbage_list	*next;
}	t_garbage_list;

/*
 * Core functions :.
*/

void				ft_minishell(void);
int					argv_error_handler(char *argv);
void					ft_free_fd(void);
char				*ft_prompt(void);
char				*read_line(void);
void				ft_executor(char *line);
void				ft_add_history(char *line);

/*
 * Functions to debug and track states of output :
*/

void				ft_print_env(char **env);
void				ft_print_token(t_token *token);
void				disp_tree(t_node *tree, int lev);
void				ft_print_simple_cmd(char **argv);

/*
 * LEXER FUNCTIONS :
*/

t_node				*ft_lexer_parser_program(char *line);
bool				constructor_token_list(char *in_characters, \
		t_token **token_list);
t_token				*retrieve_next_token(char *in_characters, int *i);
t_token				*tokenize_word(char *in_characters, int *i);
enum e_char_type	define_char_type(char c);
enum e_char_rules	apply_rules(enum e_char_type char_types);
t_token				*token_generator(char *data, enum e_token_type type);
void				append_token(t_token *new_token, t_token **token_list);
t_token				*tokenize_lesser(char *in_characters, int *i);
t_token				*tokenize_greater(char *in_characters, int *i);
t_token				*tokenize_parentheses(char *in_characters, int *i);
t_token				*tokenize_and(char *in_characters, int *i);
t_token				*tokenize_semicolon(char *in_characters, int *i);
t_token				*tokenize_pipe(char *in_characters, int *i);

/*
 * Garbage Memory collection functions, to allocate, initialize, delete...
*/

void				*garbage_malloc(size_t size);
t_garbage_list		**get_garbage_list(void);
void				garbage_bzero(void *memory, size_t n);
void				garbage_memdel(void **memory);
void				garbage_free(void **garbage_to_free);
void				garbage_free_everything(void);
void				garbage_exit(int status, char *msg);
void				garbage_putstr_fd(int fd, char const *str);
void				ft_free_all_leaks(void);
/*
 * PARSER FUNCTIONS :
*/

bool				ast_constructor(t_token **token_list, t_node **ast, \
		bool is_subshell);
bool				check_logical_operators(enum e_token_type type);
bool				logical_operators_parser(t_token **token_list, t_node \
		**ast, bool is_subshell);
void				token_devour(t_token **token_list);
bool				pipe_parser(t_token **token_list, t_node **ast, \
		bool is_subshell);
bool				simple_command_parser(t_token **token, t_node **ast, \
		bool is_subshell);
bool				identify_leaf(enum e_token_type type);
bool				identify_redirection(enum e_token_type type);
bool				identify_parenthesis(enum e_token_type type);
bool				convert_list_to_array(t_token **token_list, t_node \
		*simple_cmd, bool is_subshell);
bool				printerror_and_falsify(bool is_subshell);
bool				check_errors(t_token *token_list);

/*
 * Libft utils :
*/

char				*ft_strndup(const char *str, size_t n);
size_t				ft_strnlen(char const *str, size_t max_len);
void				*ft_memcpy(void *dest, void const *src, size_t n);
size_t				ft_strlen(char const *str);
size_t				ft_strlcpy(char *dest, char const *src, size_t destsize);
void				ft_bzero(void *memory, size_t size);
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strdup(const char *s);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**ft_split(const char *s, char c);
char				*ft_strcat(char *dest, char *src);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strjoin(char const *s1, char const *s2, \
		char const *sep);
void				ft_free_arrays(char **arrays);
char				*ft_itoa(int n);
int					ft_atoi(const char *s);
int					ft_putstr_fd(char const *s, int fd);
char				*ft_strncpy(char *dest, char *src, int size);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_putendl(char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
char				*ft_stringjoin(char const *s1, char const *s2);
int					get_next_line(int fd, char **line);
char				*ft_append_char(char *str, char c);
int					ft_isprint(int c);
int					ft_striter(char *str, int (*function) (int));
/*
 * Pipe streams define
 * I had enums flipped LOL
*/

enum e_pipe
{
	OUTPUT,
	INPUT
};

# define PATH_AS_DEFAULT "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:\
/sbin:/bin"
# define CMD_ERROR "Minishell : cmd error\n"
# define EXIT_COMMAND_NOT_FOUND 127
# define ENV_FILE "/tmp/.env"

/*
 * EXECUTION ABSTRACTION :
*/

void				execute_ast_data(t_node *ast);
void				ft_complex_exec(t_node *ast, bool pipe);
void				ft_exec_simple_cmd(t_simple_cmd cmd);
int					system_run(char **argv);
char				*verify_bin_path(char **argv);
char				*retrieve_bin_path(const char *binary);
int					ft_exec_manager(char *binary_path, char *cmd);
int					error_manager(char *binary_path, char *cmd, char *error, \
int exit_val);
bool				ft_is_executable(char *binary_path);
void				exec_in_parent(int pid);

/*
 * Env typedef :
*/

typedef char	**t_env;

/*
 * Init shell environment.
*/

int					init_bash_env(char *shell, t_env env);
void				init_env_variables(char *shell);
char				*get_true_filepath(char const *filepath);
char				*path_extracter(char const *filepath);
char				*realpath_helper(char const *path);
char				*file_extract(char *filepath);
t_env				*get_bash_env(void);
int					env_length(t_env env);
char				*get_env(const char *var);
int					ft_in_env(const char *var);
void				ft_set_env_var(const char *name, const char*val, \
		int replace);
char				**ft_add_up_in_env(const char *name, const char *val, \
		t_env env);
void				cleaner_mr_propre(char *tmp_path, char *shell_path, \
		char *shelvl_value);
int					retrieve_len_array(char **array);
char				**env_reader(char *name);
int					ft_read_char_arr_fd(char ***array, int fd);
char				*get_env_array(char *name, char **envp);
char				*search_for_env_val(char *var, char *name);
void				free_chararray(char **array);

/*
 * Minishell exit ==> return exit_status and free all data.
*/

void				shell_exit(int status, char *msg);
int					*retrieve_exit_status(void);
void				exit_value_set(int exit_value);

/*
 * Variadic function to print arbitrary number of errors on given fd stream
*/

int					variadic_error_printer(int fd, const char *fmt, ...);

/*
 * variadic defines and utils :
*/

# define BUFFERING 4096

typedef struct s_buffering
{
	int		i;
	char	buffer[BUFFERING];
}	t_buffering;

typedef struct s_converter
{
	char	type;
	void	(*function)(t_buffering *, va_list);
}	t_converter;

char				*variadic_format(const char *str, va_list ap);
int					type_recognizer(char type, va_list ap, t_buffering *fmt);
void				convert_percent(t_buffering *fmt, va_list ap);
void				convert_c(t_buffering *fmt, va_list ap);
void				convert_s(t_buffering *fmt, va_list ap);
void				convert_d(t_buffering *fmt, va_list ap);

/*
 * LEAKS FIGHTING :
*/

void	ast_clearing(t_node **ast);
void	simple_cmd_clearing(t_node **simple_cmd);
void	tokens_clearing(t_token **token_list);

/*
 * I/O streams file struct :
*/

typedef struct s_io_streams_file
{
	int	input_stream;
	int	output_stream;
}	t_io_streams_file;

/*
 * IO_STREAMS UTILS :
*/

void	ft_close_fd(t_io_streams_file saver);

/*
 * EXECUTE REDIRRECTONS : 
*/

bool				execute_redirections(t_node *ast);
bool				scan_open_redirections(char **argv, int *fd_input, \
		int *ft_output, bool input_has_quotes);
bool				arg_content_is_redirected(char *arguments);
bool				is_redirection(char **arguments, int *fd_input, \
		int *fd_output, bool input_has_quotes);
int					input_stream_redirection(char const *io_stream);
int					output_stream_redirection(char **arguments);
void				delete_redirections_in_argv(char **arguments);
t_io_streams_file	*retrieve_io(void);
void				exec_in_child(t_simple_cmd cmd, t_io_streams_file saver);

/*
 * PIPES :
*/

void				ft_pipe_setter(bool val);
bool				*ft_pipe_getter(void);
void				execute_pipes(t_node *ast);
void				pipe_child_process(t_node *ast, int file_descriptor[2], \
t_io_streams_file *saver);

/*
 * COMMAND LIST :
*/

void				execute_commands_list(t_node *ast);
void				execute_logical_and_node(t_node *ast);
void				execute_logical_or_nodee(t_node *ast);
void				execute_semicolon_node(t_node *ast);
bool				shell_expansions(t_node *ast);

/*
 * SIGNALS HANDLING:
*/

void				terminal_initialization(int status);
void				reset_term(struct termios	*terminal);
void				ignoring_signals(int signal);
void				signal_receiver(int signal, siginfo_t *infos, void *opt);
void				wait_for_signals(int signal, void (*handler)(int, \
			siginfo_t *, void *));
void				toggle_signals(int toggle);
void				handling_sigquit(int signal);
void				handling_sigint(int signal, siginfo_t *info, void *ctx);

#endif
