/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_replace_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:38:12 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/20 17:44:24 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ms_get_next_word(char *str)
{
	char	*word;
	int		i;

	i = 0;
	while (ft_isspace(str[i]) != 1 && str[i] != '\0')
	{
		if ((str[i] == '$') && (i != 0))
			break ;
		i++;
	}
	word = ft_substr(str, 0, i);
	return (word);
}

void	ms_word_replace(t_ms_data *ms, int i, char *del, char *repl)
{
	char *tmp1;
	char *tmp2;
	char *tmp3;
	char *tmp4;

	tmp1 = ft_substr(ms->line, 0, i);
	tmp2 = ft_substr(ms->line, i + ft_strlen(del), ft_strlen(ms->line));
	tmp3 = ft_strdup(repl);
	if (tmp3[0] == '\0' && tmp1[i - 1] == ' ' && tmp2[0] == ' ')
	{
		tmp4 = tmp2;
		tmp2 = ft_strtrim(tmp2, " ");
		free(tmp4);
	}
	tmp4 = ft_strjoin(tmp1, tmp3);
	free(tmp1);
	free(tmp3);
	tmp1 = ft_strjoin(tmp4, tmp2);
	free(tmp4);
	free(tmp2);
	tmp3 = ms->line;
	ms->line = tmp1;
	free(tmp3);
	printf("\n");
}

void	ms_replace_variable(t_ms_data *ms, int *i, char *word)
{
	t_ms_env_variable	*curr;

	curr = ms->env_vars_head;
	while (curr != NULL)
	{
		if (mst_isequal_str(curr->name, word + 1) == 1)
		{
			ms_word_replace(ms, *i, word, curr->content);
			return ;
		}
		curr = curr->next;
	}
	ms_word_replace(ms, *i, word, "");
}

int	ms_replace_args(t_ms_data *ms)
{
	int		i;
	char	*line_cpy;
	char	*word;

	i = 0;
	while(ms->line[i] != '\0')
	{
		if (ms->line[i] == '$')
			if (ms->line[i + 1] != '\0' && ms->line[i + 1] != '$' && ft_isspace(ms->line[i + 1]) != 1)
			{
				line_cpy = ms->line + i;
				word = ms_get_next_word(line_cpy);

				ms_replace_variable(ms, &i, word);
				free(word);
				word = NULL;
				i--;
			}
		i++;
	}
	return (0);
}

