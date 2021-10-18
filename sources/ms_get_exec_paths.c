/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_exec_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:43:05 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/18 12:50:04 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ms_get_exec_paths(t_ms_data *ms)
{
	t_ms_env_variable	*curr;

	curr = ms->env_vars_head;
	while (curr != NULL)
	{
		if (ft_strnstr(curr->env_variable, "PATH", 6) != NULL)
		curr = curr->next;
	}
	return (0);
}
