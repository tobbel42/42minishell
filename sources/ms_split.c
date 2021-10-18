/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:04:59 by tgrossma          #+#    #+#             */
/*   Updated: 2021/10/18 16:37:34 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	free_array(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		printf("hello %s\n", tab[i]);
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	printf("hello world\n");
	free(tab);
}

static char	*next_arg(char *line, int *index)
{
	char	*sub;
	char	quote;
	int		i;

	while (line[*index] == ' ')
		*index = *index + 1;
	i = *index;
	while (line && line[i] && line[i] != ' ')
	{	
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
			{
				if (quote == '\"' && line[i] == '\\')
					i++;
				i++;
			}
		}
		i++;
	}
	sub = ft_substr(line, *index, i - *index + 1);
	*index = i;
	return (sub);
}

static int	count_arg(char *line)
{
	int	count;
	char quote;
	int	i;

	if (!line)
		return (0);
	i = 0;
	count = 1;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i++])
	{
		if (line[i] == ' ')
		{
			count++;
			while (line[i] == ' ')
				i++;
		}
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			while (line[i++] && line[i] != quote)
			{
				if (quote == '\"' && line[i] == '\\')
					i++;
			}
		}
	}
	return (count);
}

// static char	**free_helper(char **array, char *arg)
// {
// 	if (arg)
// 		free(arg);
// 	if (array)
// 		free_array(array);
// 	return (NULL);
// }


// char **append_arg(char **array, char *arg)
// {
// 	int		i;
// 	char	**tab;
	
// 	// if (!array || !arg)
// 	// 	return (free_helper(array, arg));
// 	i = 0;
// 	while (array[i])
// 		i++;
// 	tab = (char **)ft_calloc(i + 2, sizeof(char *));
// 	// if (!tab)
// 	// 	return (free_helper(array, arg));
// 	i = 0;
// 	while (array[i])
// 	{
// 		tab[i] = array[i];
// 		i++;
// 	}
// 	tab[i] = arg;
// 	//free_array(array);
// 	return (tab);
// }


int	ms_split(t_ms_data *ms_data)
{
	int		n;
	int		c;
	int		i;	
	char	**tab;

	if (!ms_data || !ms_data->line)
		return (1);
	c = count_arg(ms_data->line);
	tab = (char **)ft_calloc(c + 1, sizeof(char *));
	n = 0;
	i = 0;
	while (i < c)
	{
		tab[i] = next_arg(ms_data->line, &n);
		if (tab[i] == NULL)
		{
			free_array(tab);
			tab = NULL;
			return (1);
		}
		i++;
	}
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}
