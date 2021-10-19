# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 15:34:59 by akamlah           #+#    #+#              #
#    Updated: 2021/10/19 16:00:05 by akamlah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ms_tools.a
CC = gcc
C_FLAGS = -Wall -Wextra -Werror
CFILES = mst_word_replace.c \
	mst_get_next_word.c \
	mst_isequal_string.c \
	mst_free_char2.c \


OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -crs $@ $^

%.o: %.c 
	$(CC) $(C_FLAGS) $< -c -o $@

re:
	make fclean
	make all

clean:
	rm -f $(OBJECTS)

fclean:
	make clean
	rm -f $(NAME)
