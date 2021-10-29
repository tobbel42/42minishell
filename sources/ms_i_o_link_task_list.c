#include "../header/minishell.h"

/*
//tries to open the infile, and passes the fd to the next cmd
//if the file cant be open whatsoever an empty pipe is passed to the nxt cmd
*/
void	ms_iolink_infile(t_ms_task *task)
{
	int	fd;

	fd = open(task->args[1], O_RDONLY);
	if (fd == -1)
	{
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
		if (task->next)
			task->next->err_flag = 2;
	}
	else if (task->next)
		task->next->fd_in = fd;
}

/*
//opens the outfile in the either 0 -> truncate or 1 -> append mode
//if the file cant be opend, a blackhole-pipe is created
*/
void	ms_iolink_outfile(t_ms_task *task, int mode)
{
	int	fd;
	int	p[2];

	fd = 0;
	if (mode == 0)
		fd = open(task->args[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (mode == 1)
		fd = open(task->args[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
		pipe(p); // todo pipeprotect
		fd = p[1];
		close(p[0]);
	}
	if (task->prev)
		task->prev->fd_out = fd;
}

void	ms_iolink_pipe(t_ms_task *task)
{
	int	fd[2];
	int	err;

	if (!task->prev || !task->next)
		return ;
	err = pipe(fd);
	if (!err)
	{
		task->prev->fd_out = fd[1];
		task->next->fd_in = fd[0];
	}
	else
	{
		task->prev->err_flag = 2;
		task->next->err_flag = 2;
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
	}
}

void	ms_iolink_heredoc(t_ms_task	*task)
{
	//toDo: launch as seperate process, different check for exit, safty
	char	*line;
	int		fd[2];

	pipe(fd);
	task->next->fd_in = fd[0];
	ft_putchar_fd('>', 1);
	line = get_next_line(0);
	printf("%s\n", line);
	while (line && ft_strncmp(task->args[1], line, (int)ft_strlen(task->args[1]) + 1))
	{
		ft_putchar_fd('>', 1);
		ft_putstr_fd(line, fd[1]);
		if (line)
			free (line);
		line = get_next_line(0);
		printf("%s\n", line);
	}
	if (line)
		free(line);
	close(fd[1]);
}

// goes through tasks and sets the file descriptors according to the special
// characters
void	ms_iolinking_task_list(t_ms_data *ms)
{
	t_ms_task	*curr;

	curr = ms->task_list;
	while (curr != NULL)
	{
		if (mst_isequal_str(curr->name, "<") == 1)
			ms_iolink_infile(curr);
		if (mst_isequal_str(curr->name, "<<") == 1)
 			ms_iolink_heredoc(curr);
		if (mst_isequal_str(curr->name, ">>") == 1)
			ms_iolink_outfile(curr, 1);
		if (mst_isequal_str(curr->name, ">") == 1)
			ms_iolink_outfile(curr, 0);
		if (mst_isequal_str(curr->name, "|") == 1)
			ms_iolink_pipe(curr);
		curr = curr->next;
	}
}
