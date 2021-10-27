/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:28:56 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/27 12:40:55 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// writes the environmental variables into a char** allocating memory for it.
// if allocation fails, null is returned.
char	**ms_env_to_array(t_ms_data *ms)
{
	t_ms_env_variable	*curr;
	char				**env_arr;
	int					i;

	curr = ms->env_vars_head;
	i = 0;
	env_arr = malloc(sizeof(char *) * (ms->env_lines_count + 1));
	if (!env_arr)
		return (NULL);
	while (curr != NULL)
	{
		env_arr[i] = ft_strdup(curr->all);
		if (!env_arr[i])
		{
			ms_free_char2(env_arr);
			return (NULL);
		}
		// printf("ENV ARR %d: %s\n", i, env_arr[i]);
		curr = curr->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

// writes the env. variables' list to stdout
void	ms_print_env_list(t_ms_data *ms)
{
	t_ms_env_variable	*curr;

	curr = ms->env_vars_head;
	while (curr != NULL)
	{
		write(1, curr->all, ft_strlen(curr->all));
		write(1, "\n", 1);
		curr = curr->next;
	}
}