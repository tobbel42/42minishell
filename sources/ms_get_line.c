/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:19:45 by tgrossma          #+#    #+#             */
/*   Updated: 2021/10/20 13:00:09 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
//on incomming Ctrl + C a new prompt is printed
*/
static void	sig_handler(int num)
{
	num = 1;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
//reads from stdin, till a full line is entered
//frees ms_data->line, if not NULL
//returns 0 on success, 1 on error
*/
int	ms_get_line(t_ms_data *ms_data)
{
	char	*line;

	if (!ms_data)
		return (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	if (ms_data->line)
	{
		free(ms_data->line);
		ms_data->line = NULL;
	}
	line = readline("minishell> ");
	if (!line)
		ms_free_and_exit(ms_data, 1, EXIT_SUCCESS);
	add_history(line);
	ms_data->line = line;
	return (0);
}
