#include "../header/minishell.h"

static char	*quote_replace(char **line, int i, int j)
{
	char	*new_line;
	int		len;
	int		c;
	int		d;

	len = ft_strlen(*line);
	new_line = (char *)ft_calloc(len - 1, sizeof(char));
	if (!new_line)
		return (NULL);
	c = 0;
	d = 0;
	while (c < len - 2)
	{
		if (c == i || c == j - 1)
			d++;
		new_line[c] = (*line)[c + d];
		c++;
	}
	free(*line);
	return (new_line);
}

static int	quote_find(char **line, int i)
{
	int		j;
	char	quote;

	quote = (*line)[i];
	j = 1;
	while ((*line)[i + j] && (*line)[i + j] != quote)
		j++;
	if ((*line)[i + j] == quote)
	{
		*line = quote_replace(line, i, j + i);
		return (i + j - 2);
	}
	return (1);
}

static void	str_to_lower(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = (int)ft_strlen(str);
	while (i < len)
	{	
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

/*
//cleans the input ny parsing closed quotes from the argument
*/
char	*ms_clean_input(char *arg, int mode)
{
	int		i;
	char	*new_line;

	if (!arg)
		return (NULL);
	i = 0;
	new_line = ft_strdup(arg);
	if (!new_line)
		return (NULL);
	while (new_line[i])
	{
		if (new_line[i] == '\"' || new_line[i] == '\'')
		{
			i = i + quote_find(&new_line, i);
		}
		if (new_line[i])
			i++;
	}
	if (mode == 0)
		str_to_lower(new_line);
	return (new_line);
}
