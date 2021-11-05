#include "../header/minishell.h"

/*
//returns 1 if quotes are unclosed, or the lenght of the quote if closed
*/
static int	quote_skip(char *line)
{
	int		i;
	char	quote;

	quote = line[0];
	i = 1;
	while (line[i])
	{
		if (line[i] == quote)
			return (i + 1);
		i++;
	}
	return (1);
}

static void	ms_replace_number(t_ms_data *ms, int i)
{
	int	j;
	char tok[3];

	j = 0;
	while (j < 2)
	{
		tok[j] = ms->line[j + i];
		j++;
	}
	tok[j] = '\0';
	ms_token_replace(ms, i, tok, "");
}

/*
	Iterates through the line read and repplaces every word countersigned with '$'
	with the content of the corresponding variable in env, or deletes the word from
	the line if no such variable was found. Variables in sinqle quotes do not
	get replaced, except the statement is enclosed in double quotes.
*/
int	ms_replace_args(t_ms_data *ms)
{
	int		i;
	int		dqflag;

	i = 0;
	dqflag = -1;
	while (ms->line[i] != '\0')
	{
		if (ms->line[i] == '\'' && dqflag == -1)
			i += quote_skip(ms->line + i);
		else
		{
			if (ms->line[i] == '\"' && quote_skip(ms->line + i) != 1)
				dqflag *= -1;
			if ((ms->line[i] == '$') && (ms->line[i + 1] != '\0' && \
				ms->line[i + 1] != '$' && ft_isspace(ms->line[i + 1]) != 1))
				if (ft_isdigit(ms->line[i + 1]) != 1)
					ms_replace_variable(ms, i);
				else
				{
					ms_replace_number(ms, i);
					// i++;
				}
			else
				i++;
		}
	}
	return (0);
}
