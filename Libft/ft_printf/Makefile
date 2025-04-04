# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdhallen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:17:46 by jdhallen          #+#    #+#              #
#    Updated: 2024/10/30 09:19:27 by jdhallen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
NAME = ft_libftprintf.a

SRC = ft_printf.c ft_putchar_n.c ft_puthexamaj_n.c ft_puthexamin_n.c \
	ft_putnbr_n.c ft_putstr_n.c ft_putunnbr_n.c ft_putp_n.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
