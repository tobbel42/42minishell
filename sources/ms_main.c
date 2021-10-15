/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:55:04 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/15 15:10:23 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


	// if (!= 0)
		// free and exit

void	ms_init_data(t_ms_data *ms)
{
	ms->line = NULL;
	ms->env_head = NULL;
	ms->paths = NULL;
	ms->pipex = NULL;
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