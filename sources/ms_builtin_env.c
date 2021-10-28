/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:46:01 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/27 15:47:36 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header/minishell.h"

int	ms_builtin_env(t_ms_data *ms, t_ms_task *task)
{
	printf("HI HI!\n");
	ms_print_env_list(ms);
	printf("%s\n", task->args[0]);
	return (0);
}