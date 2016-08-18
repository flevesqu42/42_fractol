# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/17 06:36:42 by flevesqu          #+#    #+#              #
#    Updated: 2016/04/28 07:42:18 by flevesqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

INCLUDES = libft/includes/

SRC = main.c\
	  julia.c\
	  mandelbrot.c\
	  init.c\
	  key_functions.c\
	  burning_ship.c\
	  colors.c\
	  burning_julia.c\
	  buddhabrot.c\
	  burning_ghost.c\
	  julia_ghost.c\
	  light.c

WFLAGS = -Wall -Werror -Wextra -O3 -march=native -ffast-math

LFLAGS = -L libft/ -lft -lm -lmlx -framework OpenGL -framework AppKit

CC = gcc

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o: %.c $(NAME).h
	$(CC) -c $(WFLAGS) -I $(INCLUDES) $< -o $@

$(NAME) : $(OBJ) $(NAME).h
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(WFLAGS) $(LFLAGS)

clean :
	rm -rf $(OBJ)

lclean :
	make -C libft/ clean

fclean : clean
	rm -f $(NAME)

lfclean :
	make -C libft/ fclean

re : fclean all

lre :
	make -C libft/ re

.PHONY: all clean fclean re lclean lfclean lre
