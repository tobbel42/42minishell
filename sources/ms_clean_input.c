#include "../header/minishell.h"

/*
//removes the quotes on position i and i + j in the given string
*/
static char	*quote_replace(char *line, int i, int j)
{
	char	*new_line;
	int		len;
	int		c;
	int		d;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	new_line = (char *)ft_calloc(len - 1, sizeof(char));
	if (!new_line)
		return (NULL);
	c = 0;
	d = 0;
	while (line[d])
	{
		if (!(d == i || d == i + j))
		{
			new_line[c] = line[d];
			c++;
		}
		d++;
	}
	free(line);
	return (new_line);
}

/*
//searches the string for a quote pair, if found they are removed
//and the index is set to the position after them
*/
static char	*quote_find(char *line, int *index)
{
	int		j;
	int		i;
	char	quote;

	if (!line)
		return (NULL);                 
	i = *index;
	j = 1;
	quote = line[i];
	while (line[i + j] && line[i + j] != quote)
		j++;
	if (line[i + j])
	{
		line = quote_replace(line, i, j);
		*index = *index + j - 2;
	}
	return (line);
}

/*
//transforms the string to lowercase
*/
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
//cleans the input by parsing closed quotes from the argument
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
	while (new_line && new_line[i])
	{
		if (new_line[i] == '\"' || new_line[i] == '\'')
			new_line = quote_find(new_line, &i);
		i++;
	}
	if (mode == 0)
		str_to_lower(new_line);
	return (new_line);
}
