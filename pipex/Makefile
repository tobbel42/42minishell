# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 11:20:52 by akamlah           #+#    #+#              #
#    Updated: 2021/10/15 14:37:03 by tgrossma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

CFLAGS = -Wall -Wextra -Werror
CC = gcc

LFT_PATH = ../libft
LIBFT = make -C $(LFT_PATH)

CFILES =ppx_files.c \
ppx_get_exec_paths.c \
ppx_parse_commands.c \
ppx_cmd_utils.c \
ppx_execute_commands.c \
ppx_exit_and_free.c \
ppx_libft_additions.c \

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(LIBFT)
	ar -crs $@ $^

clean: clean_libft
	rm -f *.o

fclean: clean fclean_libft
	rm -f $(NAME) *~

re: fclean all

clean_libft:
	make clean -C $(LFT_PATH)

fclean_libft:
	make fclean -C $(LFT_PATH)
