#include "../header/minishell.h"

void	ms_iolink_infile(t_ms_task *task)
{
	if(mst_isequal_str(task->args[0], "<") != 1 || !task->args[1] || task->args[2])
		return ;
	task->fd_in = open(task->args[1], O_RDONLY);
	if (task->fd_in < 0)
	{
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
	}
}

/*
//opens the outfile in the either 0 -> truncate or 1 -> append mode
//if the file cant be opend, a blackhole-pipe is created
*/
void	ms_iolink_outfile(t_ms_task *task, int mode)
{
	int fd;
	int p[2];

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
		task->prev->fd_out = p[1];
		close(p[0]);
		return ;
	}
	if (task->prev)
		task->prev->fd_out = fd;
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
		// if (curr->name && curr->name[0])
		// {
		// 	if (mst_isequal_str(curr->name, "<<") == 1)
		// 		//  todo
		if (mst_isequal_str(curr->name, ">>") == 1)
			ms_iolink_outfile(curr, 1);
		if (mst_isequal_str(curr->name, ">") == 1)
			ms_iolink_outfile(curr, 0);
		// 	if (mst_isequal_str(curr->name, "|") == 1)
		// 		// todo
		// }
		curr = curr->next;
	}
}
