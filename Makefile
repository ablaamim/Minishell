# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 17:25:54 by ablaamim          #+#    #+#              #
#    Updated: 2022/06/08 17:41:53 by ablaamim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
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
      ./srcs/contructor_token_list.c

OBJ = $(patsubst %.c,%.o,$(SRC))

all : $(NAME)

bonus : $(NAME_B)

# MAC OS

#$(NAME) : $(OBJ)
#	$(CC) $(RFLAGS) $(OBJ) $(CFLAGS) -o $(NAME)

# LINUX

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(RFLAGS) -o $(NAME)


%.o:	%.c Makefile $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) minishell

re: fclean all

.PHONY: all clean fclean re
