/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:51:23 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/18 12:48:07 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
// takes a string as parameter and creates a new node in the list of the
// environmental variables containing that string.
*/
int	ms_env_add(t_ms_data *ms, char *env_variable)
{
	t_ms_env_variable	*new_env_variable;

	new_env_variable = malloc(sizeof(t_ms_env_variable));
	if (new_env_variable == NULL)
		return (-1);
		// if we prefer to malloc also the string:
		// new_env_variable->env_variable = ft_strdup(envp[i]);
	new_env_variable->env_variable = env_variable;
	new_env_variable->next = ms->env_vars_head;
	ms->env_vars_head = new_env_variable;
	return (0);
}

/*
// itertates through envp and saves every substring as a node of the
// env. variable's linked list on its own.
// if error during allocation, frees already allocated elements and 
// returns -1
*/
int	ms_get_env(t_ms_data *ms, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ms_env_add(ms, envp[i]) != 0)
		{
			ms_free_env_list(ms);
			return (-1);
		}
		// TEST
		// printf("%s\n", ms->env_vars_head->env_variable);
		i++;
	}
	return (0);
}
