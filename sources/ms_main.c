/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:55:04 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/15 11:17:32 by akamlah          ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
	t_ms_data	ms;

	// 1 init -> zeros
	ms_init_data(&ms);

	// 2 get env


	// get cmd paths


	// 3 get line


	// 4 replace args $


	// 5 split


	// 6 get cmds


	// 7 execute


	return (0);
}