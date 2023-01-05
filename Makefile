# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/03 12:25:28 by jwon              #+#    #+#              #
#    Updated: 2022/10/16 15:40:43 by miozkan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRCS	= ft_printf.c \
		  parse.c \
		  print.c \
		  utils.c

OBJS	= ${SRCS:%.c=%.o}

FLAGS	= -Wall -Wextra -Werror

$(NAME):
	gcc $(FLAGS) -c $(SRCS) -I ./
	ar rc $(NAME) $(OBJS)

all: $(NAME)

bonus: all

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
