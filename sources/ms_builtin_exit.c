#include "../header/minishell.h"

/*
//convertes a string into an long long
//does not check for over/underflow
*/
static long long	ms_atoll(char *nptr)
{
	long long	i;
	long long	n;
	long long	sign_flag;

	n = 0;
	i = 0;
	sign_flag = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		sign_flag = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		n = (n * 10) + (nptr[i] - 48);
		i++;
	}
	return (n * sign_flag);
}

/*
	Checks that only digits or a sign in the first spot occur in the exitcode.
*/
static int	ms_isvalid_exitcode(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]) != 1)
			return (0);
		i++;
	}
	if (!(ms_atoll(s) < 9223372036854775807) || \
		!(ms_atoll(s) > -9223372036854775807))
		return (0);
	return (1);
}

/*
	exit prints everything to stderr except when redirected to outfile
*/
int	ms_builtin_exit(t_ms_data *ms, t_ms_task *task)
{
	long long	esc;

	task->fd_out = 2;
	write(task->fd_out, "exit\n", 6);
	esc = 0;
	if (task->args[1] && task->args[2] && \
		ms_isvalid_exitcode(task->args[1]) == 1)
	{
		write(task->fd_out, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	if (task->args[1] && ms_isvalid_exitcode(task->args[1]) != 1)
	{
		write(task->fd_out, "minishell: exit: ", 18);
		write(task->fd_out, task->args[1], ft_strlen(task->args[1]));
		write(task->fd_out, ": numeric argument required\n", 29);
		esc = 255;
	}
	if (task->args[1] && ms_isvalid_exitcode(task->args[1]) == 1)
		esc = ms_atoll(task->args[1]);
	write(1, "KTHXBYE\u2665\n", 11);
	rl_clear_history();
	ms_free_and_exit(ms, 1, esc);
	return (esc);
}
