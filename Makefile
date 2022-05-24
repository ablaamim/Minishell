# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 17:25:54 by ablaamim          #+#    #+#              #
#    Updated: 2022/05/24 10:53:14 by ablaamim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
FLAGS = -L/usr/local/lib -I/usr/local/include -lreadline

RM = rm -rf

HEADER = ./includes/push_swap.h

SRC = ./srcs/main.c \
	  ./srcs/ft_prompt.c \

OBJ = $(patsubst %.c,%.o,$(SRC))

all : $(NAME)

bonus : $(NAME_B)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(FLAGS) -o $(NAME)

%.o:	%.c Makefile $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) minishell

re: fclean all

.PHONY: all clean fclean re bonus
