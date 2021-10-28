# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 15:34:59 by akamlah           #+#    #+#              #
#    Updated: 2021/10/28 13:26:33 by tgrossma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ms_tools.a
NC=ms_tools
CC = gcc
C_FLAGS = -Wall -Wextra -Werror
CFILES = mst_word_replace.c \
	mst_get_next_word.c \
	mst_isequal_string.c \
	mst_free_char2.c \


OBJECTS = $(CFILES:.c=.o)

GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar -crs $@ $^
	@echo "$(GREEN)creating: $(NAME)$(NC)"

%.o: %.c 
	@$(CC) $(C_FLAGS) $< -c -o $@

re:
	@make fclean
	@make all

clean:
	@rm -f $(OBJECTS)
	@echo "$(RED)deleting: $(NAME): object-files$(NC)"

fclean:
	@make clean
	@rm -f $(NAME)
	@echo "$(RED)deleting: $(NAME)$(NC)"
