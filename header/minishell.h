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
# include <signal.h>
# include "../libft/libft.h"
# include "../pipex/pipex.h"
# include <sys/param.h>
# include <termios.h>

typedef struct s_ms_envar
{
	char				*name;
	char				*content;
	struct s_ms_envar	*next;
}						t_ms_envar;

typedef struct s_ms_task
{
	struct s_ms_task	*next;
	struct s_ms_task	*prev;
	char				*name;
	char				**args;
	char				*exec_path;
	int					fd_in;
	int					fd_out;
	int					err_flag;
	char				*err_msg;
}						t_ms_task;

typedef struct s_ms_data
{
	char		*line;
	char		**exec_paths;
	char		**split_line;
	t_ms_envar	*envars_head;
	int			env_lines_count;
	t_ms_task	*task_list;
	int			last_return;
	int			first_run_cd;
	char		*home_dir;
	int			is_pipe;
}					t_ms_data;

/*
//to relay signals for parent to child, 
//we need to save the child_process_id in a global variable
*/
int	g_pid;

// env get
int			ms_env_get(t_ms_data *ms, char **envp);
int			ms_env_add(t_ms_data *ms, char *envar_def);
// env utils
char		**ms_env_to_array(t_ms_data *ms);
void		ms_env_print(t_ms_data *ms, int fd);
void		ms_env_reverse_list(t_ms_data *ms);
t_ms_envar	*ms_get_envar(t_ms_data *ms, char *name);
int			ms_str_isequal(char *s1, char *s2);
//env new envar
t_ms_envar	*ms_env_newvar_def(char *envar_def);
t_ms_envar	*ms_env_newvar_nc(char *name, char *content);
// env add or change envar
void		ms_env_repl_content(t_ms_envar *var, char *repl);
void		ms_env_repl_envar(t_ms_envar *curr, t_ms_envar *new_var);
void		ms_env_add_after(t_ms_envar *curr, t_ms_envar *new_var);
// env free
void		ms_env_free_list(t_ms_data *ms);
void		ms_env_free_envar(t_ms_envar *ev);
// builtins
int			ms_env_valid_varname(char *name);
int			ms_builtin_export(t_ms_data *ms, t_ms_task *task);
int			ms_builtin_unset(t_ms_data *ms, t_ms_task *task);
int			ms_builtin_env(t_ms_data *ms, t_ms_task *task);
int			ms_builtin_pwd(t_ms_task *task);
int			ms_builtin_cd(t_ms_data *ms, t_ms_task *task);
int			ms_builtin_echo(t_ms_task *task);
// cd wdutils
void		ms_set_pwd(t_ms_data *ms);
void		ms_set_oldpwd(t_ms_data *ms, char *startwd);
// free
void		ms_free_and_exit(t_ms_data *ms, int exitflag, int exitstatus);
void		ms_free_char2(char **m);
// exec paths
int			ms_get_exec_paths(t_ms_data *ms);
// replace $
int			ms_replace_args(t_ms_data *ms);
// iolink
int			ms_iolinking_task_list(t_ms_data *ms);
int			ms_is_builtin(t_ms_task *task);
//input parsing functions
int			ms_get_line(t_ms_data *ms_data);
int			ms_split(t_ms_data *ms_data);
//task-list functions
int			ms_create_task_list(t_ms_data *ms_data);
void		ms_clean_task_list(t_ms_data *ms_data);
void		ms_free_task(t_ms_task *task);
char		*ms_clean_input(char *arg, int mode);
char		*ms_get_path(t_ms_task *task, t_ms_data *ms_data);
int			ms_is_cmd(char *line);
int			ms_lauch_task_list(t_ms_data *ms_data);
//redirection and pipes functions
int			ms_io_infile(t_ms_task *task);
int			ms_io_outfile(t_ms_task *task, int mode);
int			ms_io_heredoc(t_ms_task	*task);
int			ms_io_pipe(t_ms_task *task);
//utils for readline usage
void		ms_rl_sig_handler(int num);
void		ms_rl_init(void);
void		ms_rl_clean(void);

#endif
