/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_replace_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:38:12 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/26 15:50:02 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ms_get_next_token(char *str)
{
	char	*token;
	int		i;

	i = 0;
	while (ft_isspace(str[i]) != 1 && str[i] != '\0')
	{
		if ((str[i] == '$' || str[i] == '\'' || str[i] == '\"') && (i != 0))
			break ;
		i++;
	}
	token = ft_substr(str, 0, i);
	return (token);
}

void	ms_token_replace(t_ms_data *ms, int i, char *del, char *repl)
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

void	ms_replace_variable(t_ms_data *ms, int *i, char *token, int dqflag)
{
	t_ms_env_variable	*curr;

	if	((ms->line[*i - 1] == '\'' && ms->line[*i + ft_strlen(token)] == '\'') && \
		(dqflag == -1))
	{
		*i += 1;
		return ;
	}
	curr = ms->env_vars_head;
	while (curr != NULL)
	{
		if (mst_isequal_str(curr->name, token + 1) == 1)
		{
			ms_token_replace(ms, *i, token, curr->content);
			return ;
		}
		curr = curr->next;
	}
	if (mst_isequal_str("$?", token) == 1)
	{
		// replace with exit status of the most recently executed foreground pipeline
		return ;
	}
	ms_token_replace(ms, *i, token, "");
}

// i index to dollar, token will be $ folloewd by not $, not space, not null.
int	ms_replace_args(t_ms_data *ms)
{
	int		i;
	char	*line_cpy;
	char	*token;
	int		dqflag;

	i = 0;
	dqflag = -1;
	while(ms->line[i] != '\0')
	{
		if (ms->line[i] == '\"')
			dqflag *= -1;
		if ((ms->line[i] == '$') && (ms->line[i + 1] != '\0' && \
			ms->line[i + 1] != '$' && ft_isspace(ms->line[i + 1]) != 1))
		{
			line_cpy = ms->line + i;
			token = ms_get_next_token(line_cpy);
			ms_replace_variable(ms, &i, token, dqflag);
			free(token);
			token = NULL;
			i--;
		}
		i++;
	}
	// printf("i: %d LINE: %s\n", i, ms->line);
	return (0);
}

// 3.5.9 Quote Removal
// After the preceding expansions, all unquoted occurrences of the characters ‘\’, 
// ‘'’, and ‘"’ that did not result from one of the above expansions are removed.