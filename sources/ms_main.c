/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:55:04 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/18 12:50:57 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_init_data(t_ms_data *ms)
{
	ms->line = NULL;
	ms->env_vars_head = NULL;
	ms->exec_paths = NULL;
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
	

	// 3 get line
	ms_get_line(&ms);
	printf("%s\n", ms.line);
	// 4 replace args $


	// 5 split


	// 6 get cmds


	// 7 execute

	system("leaks minishell");
	return (0);
}