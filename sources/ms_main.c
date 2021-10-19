/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:55:04 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/19 20:26:34 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_init_data(t_ms_data *ms)
{
	ms->line = NULL;
	ms->env_vars_head = NULL;
	ms->exec_paths = NULL;
	ms->split_line = NULL;
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
	while (1)
	{
		ms_get_line(&ms);
		printf("%s\n", ms.line);
		printf("enter exit to quit\n");
		ms_replace_args(&ms);
		if (ms.line && !ft_strncmp("exit", ms.line, 4))
			break ;
	}
	// 4 replace args $

	// 5 split


	// 6 get cmds


	// 7 execute

	// system("leaks minishell");
	return (0);
}