/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:47:44 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/28 11:57:05 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ms_builtin_export(t_ms_data *ms, t_ms_task *task)
{
	t_ms_env_variable	*new_var;

	if (!task->args[1])// || ft_strnstr(task->args[1], "=", 1) == NULL)
		return (0);
	new_var = ms_env_new_variable(task->args[1]);
	printf("NEW VAR: %s\n", new_var->all);
	printf("line: %s\n", ms->line);
	return (0);
}