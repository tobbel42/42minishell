# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 11:20:52 by akamlah           #+#    #+#              #
#    Updated: 2021/11/04 15:07:49 by tgrossma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a
CN=pipex
CFLAGS = -Wall -Wextra -Werror
CC = gcc

CFILES = ppx_files.c \
ppx_get_exec_paths.c \
ppx_parse_commands.c \
ppx_cmd_utils.c \
ppx_execute_commands.c \
ppx_exit_and_free.c \
ppx_libft_additions.c \

OFILES = $(CFILES:.c=.o)

GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m


all: $(NAME)

$(NAME): $(OFILES)
	@ar rc $(NAME) $(OFILES) 
	@echo "$(GREEN)creating: $(NAME)$(CN)"

%.o: %.c 
	@$(CC) $(C_FLAGS) $< -c -o $@

clean:
	@rm -f $(OFILES)
	@echo "$(RED)deleting: $(CN): object-files$(NC)"

fclean: clean
	@rm -f $(NAME) *~
	@echo "$(RED)deleting: $(CN)$(NC)"

re: fclean all
	