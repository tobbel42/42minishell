/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:04:59 by tgrossma          #+#    #+#             */
/*   Updated: 2021/10/20 18:09:17 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
//jumps to the index of the closing quote, or to the next char in line
*/
static int	q_finder(char *line)
{
	int		i;
	char	q;

	q = line[0];
	i = 1;
	while (line[i] && line[i] != q)
		i++;
	if (!line[i])
		return (1);
	else
		return (i);
}

/*
//returns the next argument to the string, keeping track of the index
*/
static char	*next_arg(char *line, int *index)
{
	char	*sub;
	int		i;

	while (line[*index] == ' ')
		*index = *index + 1;
	i = *index;
	while (line && line[i] && line[i] != ' ')
	{	
		if (line[i] == '\'' || line[i] == '\"')
			i = i + q_finder(line + i);
		i++;
	}
	sub = ft_substr(line, *index, i - *index);
	*index = i;
	return (sub);
}

/*
//returns the number of arguments in the given string
*/
static void	count_arg(char *line, int *c)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			*c = *c + 1;
			while (line[i] == ' ')
				i++;
		}
		if (line[i] == '\'' || line[i] == '\"')
			i = i + q_finder(line + 1);
		i++;
	}
}

/*
//fills the array with the substrings
//returns 0 on success, 1 on error
*/
static int	fill_array(t_ms_data *ms_data, char *line, int c)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (i < c)
	{
		ms_data->split_line[i] = next_arg(line, &n);
		if (ms_data->split_line[i] == NULL)
		{
			ms_free_char2(ms_data->split_line);
			ms_data->split_line = NULL;
			free(line);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
//takes a string and split it into the single arguments
//returns 0 on success, 1 on error
*/
int	ms_split(t_ms_data *ms_data)
{
	char	*line;
	int		c;

	if (!ms_data || !ms_data->line)
		return (1);
	if (ms_data->split_line)
	{
		ms_free_char2(ms_data->split_line);
		ms_data->split_line = NULL;
	}
	line = ft_strtrim(ms_data->line, " ");
	if (!line)
		return (1);
	c = 1;
	count_arg(line, &c);
	ms_data->split_line = (char **)ft_calloc(c + 1, sizeof(char *));
	if (!ms_data->split_line)
		return (1);
	if (fill_array(ms_data, line, c) == 1)
		return (1);
	free(line);
	return (0);
}
