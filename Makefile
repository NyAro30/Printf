# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 13:38:34 by mny-aro-          #+#    #+#              #
#    Updated: 2026/03/26 18:17:53 by mny-aro-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS_COMMON = ft_putchar.c ft_putstr.c ft_putnbr.c \
			  ft_putnbr_unsigned.c ft_putnbr_hex.c ft_putptr.c
SRCS = ft_printf.c $(SRCS_COMMON)
BONUS_SRCS = ft_printf_bonus.c ft_parse_bonus.c ft_print_bonus_part1.c \
			 ft_print_bonus_part2.c ft_print_bonus_part3.c \
			 ft_utils_bonus.c ft_utils_bonus2.c $(SRCS_COMMON)

CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)
	
%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus
