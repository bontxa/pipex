# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboncine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 08:35:03 by aboncine          #+#    #+#              #
#    Updated: 2022/11/11 14:54:36 by aboncine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = main.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIB = ft_printf/libftprintf.a

%.o: %.c
	$(CC) -c $(CFLAGS) $?

all: ft_printf $(NAME)

bonus: all

ft_printf:
	cd ft_printf && $(MAKE) -s

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

clean: libftprintf_clean
	rm -f $(OBJS)

fclean: libftprintf_fclean clean
	rm -f $(NAME)

re: fclean all

libftprintf_clean:
	cd ft_printf && $(MAKE) clean

libftprintf_fclean:
	cd ft_printf && $(MAKE) fclean

.PHONY: all bonus ft_printf clean fclean re libftprintf_clean libftprintf_fclean .c.o
