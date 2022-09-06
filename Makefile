# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 17:25:54 by ablaamim          #+#    #+#              #
#    Updated: 2022/09/06 23:29:11 by ablaamim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
USER = ablaamim
NAME_B = minishell_bonus

CC = gcc

#MACOS COMPILATION :

RDLINE = -lreadline -L /Users/${USER}/.brew/opt/readline/lib -I /Users/${USER}/.brew/opt/readline/include

#LINUX COMPILATION :

LINUX_RDLINE = -lreadline

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRC = ./srcs/debug.c \
	  ./srcs/executor.c \
	  ./srcs/ft_lexer_parser_program.c \
	  ./srcs/contructor_token_list.c \
	  ./srcs/define_char_type.c \
	  ./srcs/ft_token_generator.c \
	  ./srcs/garbage_memory_collection_library.c \
	  ./srcs/libft_utils.c \
	  ./srcs/append_token.c \
	  ./srcs/tokenize_redirections.c \
	  ./srcs/tokenize_separators.c \
	  ./srcs/libft_utils_2.c \
	  ./srcs/logical_operators_parser.c \
	  ./srcs/simple_command_parser.c \
	  ./srcs/memory_utils.c \
	  ./srcs/pipe_parser.c \
	  ./srcs/ast_constructor.c \
	  ./srcs/tokens_identifier.c \
	  ./srcs/env_utils.c \
	  ./srcs/libft_utils_3.c \
	  ./srcs/libft_utils_4.c \
	  ./srcs/ft_split_strjoin.c \
	  ./srcs/ft_free_arrays.c \
	  ./srcs/copy_concatenate_utils.c \
	  ./srcs/init_shell_env.c \
	  ./srcs/file_extract.c \
	  ./srcs/ft_itoa_atoi.c \
	  ./srcs/ft_add_up_in_env.c \
	  ./srcs/mr_propre_cleaner.c \
	  ./srcs/garbage_memory_collection_library_more.c \
	  ./srcs/shell_exit.c \
	  ./srcs/variadic_error_printer.c \
	  ./srcs/variadic_format.c \
	  ./srcs/variadic_types_converter.c \
	  ./srcs/ast_clearing.c \
	  ./srcs/simple_cmd_clearing.c \
	  ./srcs/tokens_clearing.c \
	  ./srcs/expansions_performer.c \
	  ./srcs/variable_expansion.c \
	  ./srcs/remove_quotes_from_argument.c \
	  ./srcs/binary_finder.c \
	  ./srcs/exec_redirections.c \
	  ./srcs/expand_single_variable.c \
	  ./srcs/manage_execution.c \
	  ./srcs/ft_atoi.c \
	  ./srcs/ft_isdigit.c \
	  ./srcs/libft_utils_5.c \
	  ./srcs/expander_utils_2.c \
	  ./srcs/expander_utils.c \
	  ./srcs/heredoc_expander.c \
	  ./srcs/parse_parenthesis.c \
	  ./srcs/redir_helper.c \
	  ./srcs/built_in_handlers.c \
	  ./srcs/built_in_utils.c \
	  ./srcs/built_in_handlers_extanded.c \
	  ./srcs/built_in_utils_extanded.c \
	  ./srcs/execute_command_list.c \
	  ./srcs/executor_utils.c \
	  ./srcs/ft_execution_redirs.c \
	  ./srcs/executor_utils_extanded.c \
	  ./srcs/ft_handle_prompt.c \

SRC_BONUS = ./srcs/debug.c \
	  ./srcs/executor.c \
	  ./srcs/ft_lexer_parser_program.c \
	  ./srcs/contructor_token_list.c \
	  ./srcs/define_char_type.c \
	  ./srcs/ft_token_generator.c \
	  ./srcs/garbage_memory_collection_library.c \
	  ./srcs/libft_utils.c \
	  ./srcs/append_token.c \
	  ./srcs/tokenize_redirections.c \
	  ./srcs/tokenize_separators.c \
	  ./srcs/libft_utils_2.c \
	  ./srcs/logical_operators_parser.c \
	  ./srcs/simple_command_parser.c \
	  ./srcs/memory_utils.c \
	  ./srcs/pipe_parser.c \
	  ./srcs/ast_constructor.c \
	  ./srcs/tokens_identifier.c \
	  ./srcs/env_utils.c \
	  ./srcs/libft_utils_3.c \
	  ./srcs/libft_utils_4.c \
	  ./srcs/ft_split_strjoin.c \
	  ./srcs/ft_free_arrays.c \
	  ./srcs/copy_concatenate_utils.c \
	  ./srcs/init_shell_env.c \
	  ./srcs/file_extract.c \
	  ./srcs/ft_itoa_atoi.c \
	  ./srcs/ft_add_up_in_env.c \
	  ./srcs/mr_propre_cleaner.c \
	  ./srcs/garbage_memory_collection_library_more.c \
	  ./srcs/shell_exit.c \
	  ./srcs/variadic_error_printer.c \
	  ./srcs/variadic_format.c \
	  ./srcs/variadic_types_converter.c \
	  ./srcs/ast_clearing.c \
	  ./srcs/simple_cmd_clearing.c \
	  ./srcs/tokens_clearing.c \
	  ./srcs/expansions_performer.c \
	  ./srcs/variable_expansion.c \
	  ./srcs/remove_quotes_from_argument.c \
	  ./srcs/binary_finder.c \
	  ./srcs/exec_redirections.c \
	  ./srcs/expand_single_variable.c \
	  ./srcs/manage_execution.c \
	  ./srcs/ft_atoi.c \
	  ./srcs/ft_isdigit.c \
	  ./srcs/libft_utils_5.c \
	  ./srcs/expander_utils_2.c \
	  ./srcs/expander_utils.c \
	  ./srcs/heredoc_expander.c \
	  ./srcs/parse_parenthesis.c \
	  ./srcs/redir_helper.c \
	  ./srcs/built_in_handlers.c \
	  ./srcs/built_in_utils.c \
	  ./srcs/built_in_handlers_extanded.c \
	  ./srcs/built_in_utils_extanded.c \
	  ./srcs/execute_command_list.c \
	  ./srcs/executor_utils.c \
	  ./srcs/ft_execution_redirs.c \
	  ./srcs/executor_utils_extanded.c \
	  ./srcs/ft_handle_prompt.c \

OBJ = $(SRC:.c=.o)

OBJS_B = $(SRC_BONUS:.c=.o)

all : $(NAME)

bonus : $(NAME_B);

$(NAME) : $(OBJ) $(SRC)
		$(CC) $(CFLAGS) $(SRC) ./srcs/minishell.c ./srcs/ft_prompt.c $(RDLINE) -o $(NAME) #$(RDLINE)

$(NAME_B) : $(OBJS_B) $(SRC_BONUS)
		$(CC) $(CFLAGS) $(SRC_BONUS) ./srcs/minishell.c ./srcs/ft_prompt.c $(RDLINE) -o $(NAME_B)

clean:
		rm -rf $(OBJ) $(OBJS_B)

fclean: clean
		rm -rf $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re bonus
