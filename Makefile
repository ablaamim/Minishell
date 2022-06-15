# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 17:25:54 by ablaamim          #+#    #+#              #
#    Updated: 2022/06/15 17:51:46 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
# MACOS FLAG 
# RFLAGS = -lreadline
# LINUX FLAG
RFLAGS = -L/usr/local/lib -I/usr/local/inclue -lreadline

RM = rm -rf

HEADER = ./includes/minishell.h

SRC = ./srcs/minishell.c \
	  ./srcs/debug.c \
	  ./srcs/ft_prompt.c \
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
	  ./srcs/execute_abstract_syntax_tree.c \
	  ./srcs/execute_command_in_child_process.c \
	  ./srcs/system_run.c \
	  ./srcs/env_utils.c \
	  ./srcs/libft_utils_3.c \
	  ./srcs/ft_split_strjoin.c

OBJ = $(patsubst %.c,%.o,$(SRC))

all : $(NAME)

bonus : $(NAME_B)

# MAC OS COMPILATION

$(NAME) : $(OBJ)
	$(CC) $(RFLAGS) $(OBJ) $(CFLAGS) -o $(NAME)

# LINUX COMPILATION

#$(NAME) : $(OBJ)
#	$(CC) $(CFLAGS) $(OBJ) $(RFLAGS) -o $(NAME)


%.o:	%.c Makefile $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) minishell

re: fclean all

.PHONY: all clean fclean re
