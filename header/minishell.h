/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:44:07 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/28 11:54:01 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "../libft/libft.h"
# include "../pipex/pipex.h"
# include "../lib_ms_tools/ms_tools.h"

typedef struct			s_ms_env_variable
{
	char						*all;
	char						*name;
	char						*content;
	struct s_ms_env_variable	*next;
}						t_ms_env_variable;

typedef struct s_ms_task
{
	//list utils
	struct s_ms_task	*next;
	struct s_ms_task	*prev;

	//fct-basics are set during set_up-Phase
	char				*name; //cleaned up name
	char				**args; //cleaned up args
	char				*exec_path; //if a cmp -> find exec_path, else NULL;

	//I/O part are set during I/O linking phase
	int					fd_in; //default = 0
	int					fd_out; //default = 1

	//error_part
	int					err_flag; //on any error set to a value
	char				*err_msg; //is printed during exec step;
}						t_ms_task;

typedef struct s_ms_data
{
	char				*line;
	char				**exec_paths;
	char				**split_line;
	t_ms_env_variable	*env_vars_head;
	int					env_lines_count;
	t_ms_task			*task_list;
	int					last_return;
}					t_ms_data;



//alice_functions

// get env
int		ms_get_env(t_ms_data *ms, char **envp);
int		ms_env_add(t_ms_data *ms, char *env_variable);
// env tools
t_ms_env_variable	*ms_env_new_variable(char *env_variable);
char	**ms_env_to_array(t_ms_data *ms);
void	ms_print_env_list(t_ms_data *ms);
// free
void	ms_free_and_exit(t_ms_data *ms, int exitflag, int exitstatus);
void	ms_free_env_list(t_ms_data *ms);
void	ms_free_char2(char **m);
// exec paths
int		ms_get_exec_paths(t_ms_data *ms);
// replace $
int		ms_replace_args(t_ms_data *ms);
// iolink
void	ms_iolinking_task_list(t_ms_data *ms);
// builtins
int		ms_builtin_env(t_ms_data *ms, t_ms_task *task);
int		ms_builtin_export(t_ms_data *ms, t_ms_task *task);



//tobi_fuctions
int		ms_get_line(t_ms_data *ms_data);
int		ms_split(t_ms_data *ms_data);

int		ms_create_task_list(t_ms_data *ms_data);
void	ms_clean_task_list(t_ms_data *ms_data);
void	ms_free_task(t_ms_task *task);
char	*ms_clean_input(char *arg);

char	*ms_get_path(t_ms_task *task, t_ms_data *ms_data);

void	qd_launch(t_ms_data *ms_data);

int	ms_is_cmd(char *line);

int	ms_lauch_task_list(t_ms_data *ms_data);










#endif
