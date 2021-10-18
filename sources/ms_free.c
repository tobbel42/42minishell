/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:25:37 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/18 12:48:30 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// goes through dadatsructure and if entry not null frees entry
// if exitflag == 1, exits with status exitstatus
void	ms_free_and_exit(t_ms_data *ms, int exitflag, int exitstatus)
{
	ms_free_env_list(ms);
	if (ms->line != NULL)
		free(ms->line);
	if (exitflag == 1)
		exit(exitstatus);
}

/*
// frees all allocated nodes of the environmental variables' list
// as long as head != NULL (-> if list empty, does nothing.)
*/
void	ms_free_env_list(t_ms_data *ms)
{
	t_ms_env_variable	*current;
	t_ms_env_variable	*tmp;

	current = ms->env_vars_head;
	while(current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
}
