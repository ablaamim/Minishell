/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:06:31 by ablaamim          #+#    #+#             */
/*   Updated: 2022/09/06 23:27:33 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdarg.h>
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include "../Leak_Hunter/leak_hunter.h"

# define MALLOC_ERROR "Error : malloc() failed to allocate memory\n"
# define ERROR_MINISHELL_EOF "minishell : syntax error, unexpected eof\n"
# define ERROR_AND "Minishell : the '&' is not handled by program\n"
# define ERROR_TOKEN "Error : syntax error near unexpected token\n"
# define SIZEOF_ONE_CHAR_STRING 2
# define SIZEOF_TWO_CHAR_STRING 3
# define SYNTAX_ERROR_EXIT 2
# define ENV_ERROR "No such file or directory\n"
# define NUM_ARG "numeric argument required"
# define STATIC_BYTES 2560000
# define ERR -1
# define IN_REDIR "no such file or directory\n"

/*
 * LEXER CLASS ABSTRACTION.
 */

/*
 * Must contain all possible char types, during the lexing phase the proper
 * Tokenizer will be called accordingly to the type encountred whle scanning
 * input read by readline(), and apply Lexing rules, depending on if they are
 * contained inside single or double quotes.
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
 * Word token rules, its either accepted or not_accepted, will help to filter
 * data..
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
		int *fd_output, bool input_has_quotes);
 * PARSER CLASS ABSTRACTION :
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
 * command, I/O - Append - Here-doc - input redir - outpur redir.
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
 * REDIRS_LINKED_LIST
 */

typedef struct s_redirs
{
	int						fd[2];
	enum e_redirection_type	type;
	char					*file_name;
	struct s_redirs			*next;
}	t_redirs;

/*
 * Simple command, it can be composed of options (arguments), i/o stream
 * and quotes (single / double).
 */

typedef struct s_simple_cmd
{
	char		**argv;
	int			fd_in;
	int			fd_out;
	bool		input_has_quotes;
	t_redirs	*redirs;
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

typedef char	**t_env;

/*
 * Core functions :.
 */

void				ft_minishell(void);
int					argv_error_handler(char *argv);
void				ft_free_fd(void);
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
void				print_redir_list(t_redirs *redirs);

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
bool				parenthesis_parser(t_token **token_lst, t_node **ast);

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
int					ft_atoi_(const char *string);
int					ft_isdigit(int v);
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
char				*ft_append_char(char *str, char c);
int					ft_isprint(int c);
int					ft_striter(char *str, int (*function)(int));
int					ft_isalnum(int c);
int					ft_isspace(int c);
bool				has_space(char *str);
int					ft_argv_len(char **argv);
int					ft_isnumber(char *s);

/*
 * EXECUTION DATA :
 */

typedef struct s_pipe
{
	int				fd[2];
	struct s_pipe	*next;
}	t_pipe;

void				ft_iterate_tree(t_node *node, t_pipe **pipe_, \
		int *exec_index);
void				set_exit_value(int exit_value);
char				*found_binary(char **argv);
bool				execute_redirections(t_node *node);
int					manage_execution(char **binary_path, char *cmd);
int					manage_error(char *cmd, char *error, int exit_val);
void				execute_command_list(t_node *node, t_pipe **pipe_, \
		int *exec_index);
void				signal_command_child(int sig);
void				print_redir_list(t_redirs *redir);
int					*retrieve_exit_ctl_c(void);
void				ctl_c_value_set(int exit_value);
char				*get_var(char *var_name);
int					ft_lstsize(t_pipe *lst);
int					ft_isalpha(int c);
t_redirs			*redirection_generator(void);
void				redir_appender(t_redirs *new_redir, t_redirs **lst_redir);
t_redirs			*redirs_help_manager(char **args, int *fd_out, \
		t_redirs *redir);
void				ft_env_setter(char *name, char *val, int repl, t_env env);
/*
 * EXPANSIONS PERFOMER :
 */

typedef struct s_expander
{
	int		len_argv_to_append;
	int		len_old_argv;
	int		len_new_argv;
	bool	first_joined;
	bool	last_joined;
	bool	has_space;
	int		i_old;
	int		i_new;
	int		i_split;
	int		dollar_index;
}	t_expander;

/*
 * REDIR FUNCTIONS :
 */

bool				expansions_perform(t_node *ast, int remove_quotes);
void				remove_quotes_from_argument(char **argv);
void				substitute_quotes_state(char quote, bool *in_dquotes, \
		bool *in_squotes);
bool				variable_expansion(t_simple_cmd *cmd, int i);
bool				expand_single_variable(t_simple_cmd *cmd, int i, int *j, \
		bool in_dquotes);
char				*new_argument(char **argv, int len_var_name, int i, \
		char *var_val);
char				*allocate_new_argument(char *arg, int len_var_name, \
		char *var_val);
bool				ft_reallocate_arg(t_simple_cmd *cmd, int i, int *j, \
		char *var_val);
bool				verify_if_expansion_is_valid(int i, \
		char ***splitted_variable, char **argv);
bool				argument_is_redirection(char *arg);
void				expander_utils_initializer(char **argv, \
		char **splitted_variable, char *var_val, t_expander *utils);
void				manage_first_join(char *arg, char **new_arg, \
		char **splitted_variable, t_expander *utils);
void				manage_last_join(char *arg, char **new_arg, \
		char **splitted_variable, t_expander *utils);
char				*retrieve_after_variable(char *str, int dollar_index);
void				array_free(char ***array);
char				*get_variable_name(char *argument);
int					get_len_variable_name(char *argument);
char				*quotes_reversal(char *var_value);
void				heredoc_expander(char **argv);
void				get_variable_name_and_val(char *arg, char **var_name, \
		char **var_val);

/*
 * Env typedef and define :
 */

# define SIZE_10B 1024

/*
 * Init shell environment and save it in accessible memory.
 */

void				init_bash_env(char *shell, t_env env);
void				init_env_variables(char *shell);
char				*get_true_filepath(char const *filepath);
char				*path_extracter(char const *filepath);
char				*realpath_helper(char const *path);
char				*file_extract(char *filepath);
t_env				*get_bash_env(void);
int					env_length(t_env env);
char				*get_env(const char *var);
int					ft_in_env(const char *var);
char				*ft_substr(const char *src, unsigned int start, size_t len);
void				ft_set_env_var(const char *name, const char *val, \
		int replace);
char				**ft_add_up_in_env(const char *name, const char *val, \
		t_env env);
void				cleaner_mr_propre(char *tmp_path, char *shell_path, \
		char *shelvl_value);
int					retrieve_len_array(char **array);

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

void				ast_clearing(t_node **ast);
void				simple_cmd_clearing(t_node **simple_cmd);
void				tokens_clearing(t_token **token_list);

/*
 * SIGNALS HANDLING:
 */

void				signal_command(int sig);
/*
 * BUILT IN UTILS:
 */
int					ft_handle_empty_cd(char *old_pwd);
int					ft_handle_def_cd(char *argv, char *old_pwd);
int					parse_unset(char *args);
int					ft_handle_built_ins(char **args, t_node *node);
int					ft_unset_logic(char *name);
int					ft_is_built_in(char *string);
int					ft_handle_echo(char **args, t_node *node);
char				*export_variable_name(char *argument);
void				ft_echo_print(t_node *node, int i, int j, int add_new_line);
void				ft_echo_iterator(char **args, int *k, int i);
void				display_env(t_node *node);
void				export_perror(char *args, int *ret);
void				append_to_env(char *export, char *var_name);

/*
 * BUILT INS:
 */
int					ft_handle_cd(char **argv);
int					ft_handle_env(char **args, t_node *node);
int					ft_handle_pwd(t_node *node);
int					ft_handle_exit(char **args, t_node *node, int *err);
int					ft_handle_export(char **args, t_node *node);
int					ft_handle_unset(char **args);
/*
 * EXECUTION:
 */
t_pipe				*ft_lstlast(t_pipe *lst);
t_pipe				*ft_lstnew(int *fd);
DIR					*ft_open_dir(char *path, char **pattern, char **clean_path);
int					ft_argv_len(char **argv);
int					ft_is_child_ignored(char *string);
int					ft_has_wildcard(t_node *node);
int					ft_isnumber(char *s);
int					export_len_name(char *argument);
int					special_env_len(t_env *env);
int					**ft_to_array(t_pipe **pipe);
int					ft_handle_line(char *line, t_redirs *redirs, t_node *node);
int					ft_exec_cmd(t_node *node, t_pipe **pipe, int *exec_index);
char				*export_variable_name(char *argument);
char				*retrieve_var_val(char *str, char *env_val);
void				ft_lstadd_front(t_pipe **head, t_pipe *new);
void				ft_lstadd_back(t_pipe **alst, t_pipe *new);
void				ft_clean_argv(t_node *node);
void				ft_handle_existant_folder(struct dirent *entry, \
		char *clean_pattern, char *clean_path, char **argv);
void				ft_handle_wc_extraction(t_node *node, int j, char **argv);
void				ft_handle_wildcard(t_node *node);
void				export_perror(char *args, int *ret);
void				append_to_env(char *export, char *var_name);
void				ft_free_to_array(t_pipe **pipe, int **arr);
void				ft_close_pipes(t_pipe *pipe, int **arr);
void				ft_handle_heredoc(t_redirs *redirs, t_node *node, \
		int *heredoc);
void				ft_handle_redirections(t_redirs *redirs, t_node *node, \
		int *heredoc, int init_heredoc);
void				ft_handle_dup2(t_node *node, t_pipe **pipe, \
		int **pipes, int exec_index);
void				ft_handle_child_init(t_node *node, t_pipe **pipe, \
		int exec_index);
void				ft_handle_child_execution(t_node *node);
void				ft_handle_child(t_node *node, t_pipe **pipe, \
		int exec_index);
void				ft_handle_parent(t_node *node, int pid, t_pipe **pipe);
void				ft_handle_cmd(t_node *node, t_pipe **pipe, int *exec_index);
void				ft_free_pipes(t_pipe **pipe);
void				ft_handle_reset(t_pipe **pipe, int *exec_index);
void				ft_handle_dup2(t_node *node, t_pipe **pipe, \
		int **pipes, int exec_index);
void				execute_and_node(t_node *node, \
		t_pipe **pipe_, int *exec_index);
void				ft_handle_init_heredoc(t_node *node, t_pipe **pipe_, \
		int *exec_index, int *heredoc);
void				ft_init_heredoc(t_node *node, t_pipe **pipe_, \
		int *exec_index, int *heredoc);
void				execute_and_node(t_node *node, t_pipe **pipe_, \
		int *exec_index);
void				ft_iterate_tree(t_node *node, t_pipe **pipe_, \
		int *exec_index);
void				ft_hanlde_iteration(t_node *node, t_pipe **pipe_, \
		int *exec_index);
void				ft_empty_or_nodes(t_node *node, t_pipe **pipe_, \
		int *exec_index, int *heredoc);
void				ft_handle_execution(t_node *ast);
void				ft_hanlde_input_redir(t_node *node, int *heredoc, \
		t_redirs *redirs);
void				ft_handle_output_redir(t_node *node, int*heredoc, \
		t_redirs *redirs);
void				ft_handle_append_redir(t_node *node, t_redirs \
		*redirs, int *heredoc);
void				ft_handle_parent_extanded(int pid, int *status, int *gab);
void				ft_handle_parent(t_node *node, int pid, t_pipe **pipe);
char				*get_var(char *var_name);
void				ft_handle_prompt(char **line);

#endif
