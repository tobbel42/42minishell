#include "../header/minishell.h"

// goes through tasks and sets the file descriptors according to the special
// characters
int	ms_iolinking_task_list(t_ms_data *ms)
{
	t_ms_task	*curr;
	int			flag;

	curr = ms->task_list;
	flag = 0;
	while (curr != NULL && flag == 0)
	{
		if (ms_str_isequal(curr->name, "<") == 1)
			flag = ms_io_infile(curr);
		if (ms_str_isequal(curr->name, "<<") == 1)
			flag = ms_io_heredoc(curr);
		if (ms_str_isequal(curr->name, ">>") == 1)
			flag = ms_io_outfile(curr, 1);
		if (ms_str_isequal(curr->name, ">") == 1)
			flag = ms_io_outfile(curr, 0);
		if (ms_str_isequal(curr->name, "|") == 1)
			flag = ms_io_pipe(curr);
		curr = curr->next;
	}
	return (flag);
}
