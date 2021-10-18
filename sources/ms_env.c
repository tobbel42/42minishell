/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:51:23 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/18 16:10:54 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// extrapolates the variable's name from its entry in env
static void	ms_set_variable_name(t_ms_env_variable *variable)
{
	int i;

	i = 0;
	if (variable->all == NULL)
	{
		variable->name = NULL;
		return ;
	}
	while (variable->all[i] != '\0')
	{
		if (variable->all[i] == '=')
			break ;
		i++;
	}
	variable->name = ft_substr(variable->all, 0, i);
	// printf("var : %s\n", variable->all);
	// printf("name : %s\n", variable->name);
}

// extrapolates the variable's content from its entry in env
static void	ms_set_variable_content(t_ms_env_variable *variable)
{
	int i;
	int strlen;

	i = 0;
	if (variable->all == NULL)
	{
		variable->content = NULL;
		return ;
	}
	while (variable->all[i] != '\0')
	{
		if (variable->all[i] == '=')
			break ;
		i++;
	}
	strlen = ft_strlen(variable->all);
	variable->content = ft_substr(variable->all, i + 1, strlen - i - 1);
	// printf("var : %s\n", variable->all);
	// printf("content : %s\n", variable->content);
}

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
	new_env_variable->all = ft_strdup(env_variable);
	// no malloc:
	// new_env_variable->all = env_variable;
	ms_set_variable_name(new_env_variable);
	ms_set_variable_content(new_env_variable);
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
		// printf("%s\n", ms->env_vars_head->all);
		i++;
	}
	return (0);
}
