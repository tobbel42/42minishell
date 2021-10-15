# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 11:20:52 by akamlah           #+#    #+#              #
#    Updated: 2021/10/15 14:49:47 by tgrossma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

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

all: $(NAME)

$(NAME): $(OFILES)
	ar rc $(NAME) $(OFILES) 

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME) *~

re: fclean all
