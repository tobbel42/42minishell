/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:20:19 by tgrossma          #+#    #+#             */
/*   Updated: 2021/10/27 12:54:53 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ms_get_path(t_ms_task *task, t_ms_data *ms_data)
{
	int		i;
	char	*test_path;

	if (task->err_flag)
		return (NULL);
	if (!access(task->args[0], X_OK))
		return (ft_strdup(task->args[0]));
	i = 0;
	while (ms_data->exec_paths[i] && errno == ENOENT)
	{
		test_path = ft_strjoin(ms_data->exec_paths[i], task->args[0]);
		if (!test_path)
			return (NULL); 
		if (!access(test_path, X_OK))
			return(test_path);
		free(test_path);
		i++;
	}
	task->err_flag = 1;
	task->err_msg = ft_strdup(strerror(errno));
	return (NULL);
}
