/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_replace_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:38:12 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/19 20:52:09 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_replace_variable(t_ms_data *ms, int i)
{
	t_ms_env_variable	*curr;
	char				*line_cpy;
	char				*word;
	char				*tmp;
	char				*tmp2;

	line_cpy = ms->line + i; // gets rid of dollar
	word = mst_get_next_word(line_cpy);
	// printf("WORD rpl fun: %s\n", word);
	curr = ms->env_vars_head;
	while (curr != NULL)
	{
		if (mst_isequal_str(curr->name, word + 1) == 1)
		{
			tmp = ms->line;
			ms->line = mst_word_replace(tmp, i, word, curr->content);
			free(tmp);
			return ;
		}
		curr = curr->next;
	}
	tmp = ms->line;
	ms->line = mst_word_replace(tmp, i, word, "");
	free(tmp);
	// printf("line cut space: %s\n", ms->line);
	if (ms->line[i - 1] == ' ')
	{
		tmp2 = ms->line;
		// printf("tmp2 cut space: %s\n", tmp2);
		ms->line = mst_word_replace(tmp2, i, " ", "");
		free(tmp2);
	}
}

void	ms_handle_dollarsign(t_ms_data *ms, int *i)
{
	char	*line_cpy;
	char	*word;
	char	*word_cpy;

	word = NULL;
	// printf("i: %d LINE: %s\n", *i, ms->line);
	if (ms->line[*i + 1] != '$')
	{
		ms_replace_variable(ms, *i);
		// printf("FINAL LINE case 1A: %s\n", ms->line);
	}
	else if (ms->line[*i + 1] == '$')
	{
		line_cpy = ms->line + *i;
		// printf("LINE CPY case 1B: %s\n", line_cpy);
		word = mst_get_next_word(line_cpy);
		// printf("WORD case 1B: %s\n", word);
		word_cpy = word;
		// while dollars are paired, execute pair and then set ptr 2 forward.
		while (ft_strnstr(word_cpy, "$$", 2) != NULL)
		{
			// printf("couple $$\n");
			word_cpy += 2;
			*i += 2;
			// printf("WORD cpy: %s\n", word_cpy);
		}
		if (*word_cpy == '$' && (*word_cpy + 1 != '\0' && ft_isspace(*word_cpy + 1) != 1))
			ms_replace_variable(ms, *i);
		// printf("FINAL LINE case 1B: %s\n", ms->line);
	}
	free(word);
}

int	ms_replace_args(t_ms_data *ms)
{
	int i;

	i = 0;
	while(ms->line[i + 1] != '\0')
	{
		if (ms->line[i] == '$')
			if (ft_isspace(ms->line[i + 1]) != 1)// && ms->line[i + 1] != '$')
				ms_handle_dollarsign(ms, &i);
			// if ((ft_isspace(ms->line[i - 1]) == 1 && ft_isspace(ms->line[i + 1]) != 1 && ms->line[i + 1] == '$') \
			// && (ms->line[i + 2] == '\0' || ft_isspace(ms->line[i + 2]) == 1))
			// 	printf("$$ got\n");
			// 	// ms_launch_dollardollar(ms);
			// if (ms->line[i - 1] == ' ' && ms->line[i + 1] == ' ') do nothing
		i++;
	}
		printf("i: %d LINE: %s\n", i, ms->line);
	return (0);
}

// (ft_isspace(ms->line[i - 1]) == 1 || ms->line[i - 1] == '\0') && 
