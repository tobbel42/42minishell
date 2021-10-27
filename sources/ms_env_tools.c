/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:28:56 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/27 12:30:32 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**ms_env_to_array(t_ms_data *ms)
{
	t_ms_env_variable	*curr;
	char				**env_arr;
	int					i;

	curr = ms->env_vars_head;
	i = 0;
	env_arr = malloc(sizeof(char *) * (ms->env_lines_count + 1));
	while (curr != NULL)
	{
		env_arr[i] = ft_strdup(curr->all);
		// printf("ENV ARR %d: %s\n", i, env_arr[i]);
		curr = curr->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}