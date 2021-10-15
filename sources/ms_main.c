/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:55:04 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/15 12:09:01 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


	// if (!= 0)
		// free and exit

void	ms_init_data(t_ms_data *ms)
{
	ms->line = NULL;
	ms->env = NULL;
	ms->paths = NULL;
}

int main(void)
{
	t_ms_data	ms;

	// 1 init -> zeros
	ms_init_data(&ms);

	// 2 get env


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