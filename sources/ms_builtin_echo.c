#include "../header/minishell.h"

static int	ms_is_nflag(char *str)
{
	int	i;
	
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*
	Function that writes to given fd the arguments following
	the command "echo", with a final newline which is suppressed
	if -n option is specified.
*/
int	ms_builtin_echo(t_ms_task *task)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 1;
	if (ms_is_nflag(task->args[1]) == 1)
	{
		n_flag = 1;
		i = 2;
	}
	while (task->args[i])
	{	
		ft_putstr_fd(task->args[i], task->fd_out);
		i++;
		if (task->args[i])
			write(task->fd_out, " ", 1);
	}
	if (n_flag == 0)
		write(task->fd_out, "\n", 1);
	return (0);
}
