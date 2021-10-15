CC=gcc
C_FLAGS=-Wall -Wextra -Werror
LFLAGS = -L$(HOME)/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$(HOME)/.brew/opt/readline/include 
NAME=minishell
SRC_DIR=./sources/
OBJ_DIR=./objects/
SRC_LIST=ms_main.c\
	ms_env.c \
	ms_get_line.c\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\

SRC=$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ=$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_LIST)))

HEADER=./header/minishell.h
GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m
LIBS= libft \
pipex \

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBS) $(HEADER)
	
	@for d in $(LIBS);\
	do\
		$(MAKE) -C $$d;\
	done;\

	@$(CC) $(C_FLAGS) $(LFLAGS) $(CPFLAGS) $(OBJ) libft/libft.a pipex/pipex.a -o $@
	@echo "\n$(GREEN)creating: $(NAME)$(NC)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@echo "$(GREEN)creating: object-files: $(NC)\c"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(C_FLAGS) $^ -c -o $@
	@echo "$(GREEN).$(NC)\c"

clean:
	@rm -f $(OBJ)
	@rm -f -d $(OBJ_DIR)

	@for d in $(LIBS);\
	do\
		$(MAKE) -C $$d clean;\
	done;\

	@echo "$(RED)deleting: object-files$(NC)"

fclean:
	@make clean
	
	@for d in $(LIBS);\
	do\
		$(MAKE) -C $$d fclean;\
	done;\

	@rm -f $(NAME)
	@echo "$(RED)deleting: $(NAME)$(NC)"

re:
	@make fclean
	@make $(NAME)

coffee:
	@echo "\n\n\n  (( (     )(("
	@echo " |====|  |====|"
	@echo "C|    |  |    |D"
	@echo " |____|  |____|"
	@echo "\n"
