/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:46:01 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/28 10:49:19 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ms_builtin_env(t_ms_data *ms, t_ms_task *task)
{
	if (task->args[1] != NULL)
		return (-1);
	ms_print_env_list(ms);
	return (0);
}