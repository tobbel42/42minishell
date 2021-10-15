/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:51:23 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/15 14:07:07 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ms_env_add(t_ms_data *ms, char *env_line)
{
	t_ms_env_line	*new_env_line;

	new_env_line = malloc(sizeof(t_ms_env_line));
	if (new_env_line == NULL)
		return (-1);
		// if we prefer to malloc also the string:
		// new_env_line->env_line = ft_strdup(envp[i]);
	new_env_line->env_line = env_line;
	new_env_line->next = ms->env_head;
	ms->env_head = new_env_line;
	return (0);
}

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
		// printf("%s\n", ms->env_head->env_line);
		i++;
	}
	return (0);
}

void	ms_free_env_list(t_ms_data *ms)
{
	t_ms_env_line	*current;
	t_ms_env_line	*tmp;

	current = ms->env_head;
	while(current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
}
