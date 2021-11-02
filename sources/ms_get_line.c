#include "../header/minishell.h"

/*
//on incomming Ctrl + C a new prompt is printed
*/
static void	sig_int_handler(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sig_quit_handler(void)
{
	rl_on_new_line();
	rl_redisplay();
}

static int	init_get_line(void)
{
	struct termios	term;
	int				err_flag;

	signal(SIGQUIT, sig_quit_handler);
	signal(SIGINT, sig_int_handler);
	err_flag = tcgetattr(1, &term);
	if (!err_flag)
	{
		if ((term.c_lflag & (0x1 << 6)) == ECHOCTL)
			term.c_lflag -= ECHOCTL;
		err_flag = tcsetattr(1, 0, &term);
	}
	return (err_flag);
}

static void	clean_get_line(void)
{
	struct termios	term;
	int				err_flag;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	err_flag = tcgetattr(1, &term);
	if ((term.c_lflag & (0x1 << 6)) == 0)
	{
		term.c_lflag += ECHOCTL;
		tcsetattr(1, 0, &term);
	}
}

/*
//reads from stdin, till a full line is entered
//frees ms_data->line, if not NULL
//returns 0 on success, 1 on error
*/
int	ms_get_line(t_ms_data *ms_data)
{
	char			*line;

	if (!ms_data)
		return (1);
	if (ms_data->line)
	{
		free(ms_data->line);
		ms_data->line = NULL;
	}
	line = NULL;
	if (!init_get_line())
		line = readline("minishell> ");
	clean_get_line();
	if (!line)
		ms_free_and_exit(ms_data, 1, EXIT_SUCCESS);
	if (ft_strncmp("", line, 1))
		add_history(line);
	ms_data->line = line;
	return (0);
}
