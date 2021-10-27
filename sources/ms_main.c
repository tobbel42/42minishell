/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:55:04 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/27 12:30:52 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_init_data(t_ms_data *ms)
{
	ms->line = NULL;
	ms->env_vars_head = NULL;
	ms->env_lines_count = 0;
	ms->exec_paths = NULL;
	ms->split_line = NULL;
	ms->task_list = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_ms_data	ms;

	// 1 init -> zeros
	ms_init_data(&ms);
	argc=1;argv=NULL;
	
	// 2 get env
	if (ms_get_env(&ms, envp) != 0)
		return (-1);
	// in while loop to add env var:
	// if line = "export" -> ms_env_add(parsed line);

	// get cmd paths
	if (ms_get_exec_paths(&ms) != 0)
		ms_free_and_exit(&ms, 0, 0);
	// -> do "if (ms.exec_paths != NULL)" from here on, else segfault if unset path
	// 3 get line
	// printf("ENV LINES: %d\n", ms.env_lines_count);
	// t_ms_env_variable	*currenv;
	// currenv = ms.env_vars_head;
	// while (currenv != NULL)
	// {
	// 	printf("%s\n", currenv->all);
	// 	currenv = currenv->next;
	// }
	int i;

	// ms_env_to_array(&ms);
	while (1)
	{
		ms_get_line(&ms);
		if (!ft_strncmp("", ms.line, 1))
			continue ;
		printf("enter exit to quit\n");
		ms_replace_args(&ms);
		printf("REPL. LINE: %s\n", ms.line);
		ms_split(&ms);
		i = 0;
		while (ms.split_line[i])
		{
			printf("%i:%s\n", i, ms.split_line[i]);
			i++;
		}
		i = 0;
		while (ms.exec_paths[i])
		{
			printf("%s\n", ms.exec_paths[i]);
			i++;
		}
		ms_create_task_list(&ms);
		t_ms_task *node = ms.task_list;
		while (node)
		{
			if (node->name)
				printf("\n%s\n", node->name);
			i = 0;
			while (node->args && node->args[i])
			{
				printf("%i:%s\n", i, node->args[i]);
				i++;
			}
			node = node->next;
		}
		if (ms.line && !ft_strncmp("exit", ms.line, 4))
			break ;
	}
	// 7 execute

	system("leaks minishell");
	return (0);
}