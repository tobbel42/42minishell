/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:19:45 by tgrossma          #+#    #+#             */
/*   Updated: 2021/10/18 12:40:14 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
//checks if a not quoted \ is at the end of the line, 
//1 if yes, 0 if no
*/
static int	dash_check(char *line, int q_flag)
{
	int	len;

	if (!line || q_flag)
		return (0);
	len = ft_strlen(line);
	if ((len >= 2 && line[len - 1] == 92 && line[len - 2] != 92)
		|| (len == 1 && line[len - 1] == 92))
	{
		line[len - 1] = '\0';
		return (1);
	}
	else
		return (0);
}

/*
//checks if unclosed quotes are in the line, returns quotetype if yes, 0 if no
*/
static int	quote_check(const char *line)
{
	int		i;
	char	quote;

	if (!line)
		return (0);
	i = 0;
	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == 34 || line[i] == 39)
			&& (i == 0 || line[i - 1] != 92))
			quote = line[i];
		else if (quote && ((line[i] == 34
					&& (i == 0 || line[i - 1] != 92)) || (line[i] == 39)))
			quote = 0;
		i++;
	}
	return (quote);
}

/*
//apends a newline to the given string
*/
static char	*append_nl(char *line)
{
	char	*temp;

	if (!line)
		return (NULL);
	temp = ft_strjoin(line, "\n");
	free(line);
	return (temp);
}

/*
//appends a readline to the line
*/
static char	*append_to_line_dash(char *line, const char *promt)
{
	char	*new_line;
	char	*temp;

	if (!line)
		return (NULL);
	new_line = NULL;
	temp = NULL;
	new_line = readline(promt);
	if (new_line)
	{
		temp = ft_strjoin(line, new_line);
		free(new_line);
	}
	free(line);
	return (temp);
}

/*
//reads from stdin, till a full line is entered
//frees ms_data->line, if not NULL
//returns 0 on success, 1 on error
*/
int	ms_get_line(t_ms_data *ms_data)
{
	char	*line;
	int		q_flag;
	int		d_flag;

	if (!ms_data)
		return (1);
	if (ms_data->line)
	{
		free(ms_data->line);
		ms_data->line = NULL;
	}
	line = readline("minishell> ");
	q_flag = quote_check(line);
	d_flag = dash_check(line, q_flag);
	while (q_flag || d_flag)
	{
		if (q_flag)
			line = append_nl(line);
		line = append_to_line_dash(line, ">");
		q_flag = quote_check(line);
		d_flag = dash_check(line, q_flag);
	}
	add_history(line);
	ms_data->line = line;
	return (0);
}
