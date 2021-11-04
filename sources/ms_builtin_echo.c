#include "../header/minishell.h"

/*
	Function that writes to given fd the arguments following
	the command "echo", with a final newline which is suppressed
	if -n option is specified.
*/
int	ms_builtin_echo(t_ms_task *task)
{
	int	n_option;
	int	i;

	n_option = 0;
	i = 1;
	if (ms_str_isequal(task->args[1], "-n") == 1)
	{
		n_option = 1;
		i = 2;
	}
	while (task->args[i])
	{
		ft_putstr_fd(task->args[i], task->fd_out);
		write(task->fd_out, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(task->fd_out, "\n", 1);
	return (0);
}
