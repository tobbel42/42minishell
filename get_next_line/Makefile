# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 11:20:52 by akamlah           #+#    #+#              #
#    Updated: 2021/10/29 17:45:27 by tgrossma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
CN=get_next_line
CFLAGS = -Wall -Wextra -Werror
CC = gcc

CFILES = get_next_line.c\
	get_next_line_utils.c

OFILES = $(CFILES:.c=.o)

GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m


all: $(NAME)

$(NAME): $(OFILES)
	@ar rc $(NAME) $(OFILES) 
	@echo "$(GREEN)creating: $(NAME)$(NC)"

%.o: %.c 
	@$(CC) $(C_FLAGS) $< -c -o $@

clean:
	@rm -f $(OFILES)
	@echo "$(RED)deleting: $(CN): object-files$(NC)"

fclean: clean
	@rm -f $(NAME) *~
	@echo "$(RED)deleting: $(CN)$(NC)"

re: fclean all
	