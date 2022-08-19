# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 17:25:54 by ablaamim          #+#    #+#              #
#    Updated: 2022/08/19 02:43:14 by ablaamim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
#USER = ablaamim

CC = gcc
#MACOS COMPILATION :
RDLINE = -lreadline -L /Users/${USER}/Desktop/.brew/opt/readline/lib -I /Users/${USER}/Desktop/.brew/opt/readline/include
#LINUX COMPILATION :
LINUX_RDLINE = -lreadline

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

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
	  #./Leak_Hunter/leak_hunter.c \
	  #./Leak_Hunter/list_tools.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(SRC)
		$(CC) $(CFLAGS) $(SRC) ./srcs/minishell.c ./srcs/ft_prompt.c $(LINUX_RDLINE) -o $(NAME) #$(RDLINE)


clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
