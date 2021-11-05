#include "../header/minishell.h"

/*
	Isolates and returns a token (delimited by either space or quotes or 
	another '$')
*/
static char	*ms_get_next_token(char *str)
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

/*
	Replaces the token with new in the line.
*/
static void	ms_token_replace(t_ms_data *ms, int i, char *token, char *new)
{
	char	*new_line;
	int		len_l;
	int		len_t;
	int		len_n;

	len_l = ft_strlen(ms->line);
	len_t = ft_strlen(token);
	len_n = ft_strlen(new);
	new_line = (char *)ft_calloc(len_l - len_t + len_n, sizeof(char));
	if (!new_line)
		return ;
	ft_strlcpy(new_line, ms->line, i + 1);
	ft_strlcpy(new_line + i, new, len_n + 1);
	ft_strlcpy(new_line + i + len_n,
		ms->line + i + len_t, len_l - i - len_t + 1);
	free(ms->line);
	ms->line = new_line;
}

/*
	reads the last return value from struct and replaces '$?' with it.
*/
static void	ms_set_last_return(t_ms_data *ms, int i, char *token)
{
	char	*val;

	val = ft_itoa(ms->last_return);
	if (!val)
		return ;
	ms_token_replace(ms, i, token, val);
	free(val);
}

/*
	In this part the word is searched in the env list and the replace function
	called.
*/
void	ms_replace_variable(t_ms_data *ms, int i)
{
	t_ms_envar	*curr;
	char		*token;

	if (!ms || !ms->line)
		return ;
	token = ms_get_next_token(ms->line + i);
	if (!token)
		return ;
	curr = ms->envars_head;
	while (curr != NULL)
	{
		if (ms_str_isequal(curr->name, token + 1) == 1)
		{
			ms_token_replace(ms, i, token, curr->content);
			free(token);
			return ;
		}
		curr = curr->next;
	}
	if (ms_str_isequal("$?", token) == 1)
		ms_set_last_return(ms, i, token);
	else
		ms_token_replace(ms, i, token, "");
	free(token);
}
