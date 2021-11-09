CC=gcc
C_FLAGS=-Wall -Wextra -Werror
LFLAGS = -L$(HOME)/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$(HOME)/.brew/opt/readline/include 
NAME=minishell
SRC_DIR=./sources/
OBJ_DIR=./objects/
SRC_LIST=ms_main.c\
	ms_get_line.c\
	ms_free.c \
	ms_split.c \
	ms_get_exec_paths.c \
	ms_replace_args.c \
	ms_replace_args_utils.c \
	ms_create_task_list.c\
	ms_io_link_task_list.c \
	ms_clean_task_list.c\
\
	ms_clean_input.c\
\
	ms_get_path.c\
\
\
\
	ms_launch_task_list.c\
	ms_launch_task_list_utils.c\
\
	ms_env_get.c \
	ms_env_utils.c \
	ms_env_new_envar.c \
	ms_env_free.c \
	ms_env_add_or_change_envar.c \
	ms_builtin_env.c \
	ms_builtin_export.c \
	ms_builtin_unset.c \
	ms_builtin_pwd.c \
	ms_builtin_echo.c \
	ms_builtin_cd.c \
	ms_builtin_cd_pwdutils.c \
	ms_builtin_exit.c \
	ms_io_infile.c \
\
	ms_io_outfile.c \
\
	ms_io_heredoc.c \
\
	ms_io_pipe.c\
	ms_nice_promt.c\

SRC=$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ=$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_LIST)))

HEADER=./header/minishell.h
GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m
LIBS= libft \
#pipex


all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBS) $(HEADER)
	
	@for d in $(LIBS);\
	do\
		$(MAKE) -C $$d;\
	done;\

	@$(CC) $(C_FLAGS) $(LFLAGS) $(CPFLAGS) $(OBJ) libft/libft.a  -o $@
	@echo "$(GREEN)creating: $(NAME)$(NC)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@echo "$(GREEN)creating: object-files: $(NC)\c"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(C_FLAGS) $(CPFLAGS)  $^ -c -o $@
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
	@rm -f $(OBJ)
	@rm -f -d $(OBJ_DIR)
	@echo "$(RED)deleting: object-files$(NC)"
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
