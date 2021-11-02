#include "../header/minishell.h"

/*
	extrapolates the envar's name from its entry in env.
	If more than 1 '=', they et saved as 'content' from the second '='
	onwards.
*/
static void	ms_set_variable_name(t_ms_envar *envar, char *envar_def)
{
	int	i;

	i = 0;
	if (envar_def == NULL)
	{
		envar->name = NULL;
		return ;
	}
	while (envar_def[i] != '\0')
	{
		if (envar_def[i] == '=')
			break ;
		i++;
	}
	envar->name = ft_substr(envar_def, 0, i);
}

/*
	extrapolates the envar's content from its entry in env
*/
static void	ms_set_variable_content(t_ms_envar *envar, char *envar_def)
{
	int	i;
	int	strlen;
	int	empty_content;

	i = 0;
	empty_content = 1;
	if (envar_def == NULL)
	{
		envar->content = NULL;
		return ;
	}
	while (envar_def[i] != '\0')
	{
		if (envar_def[i] == '=')
		{
			empty_content = 0;
			break ;
		}
		i++;
	}
	strlen = ft_strlen(envar_def);
	if (empty_content == 0)
		envar->content = ft_substr(envar_def, i + 1, strlen - i - 1);
	else
		envar->content = NULL;
}

/*
	takes a string as parameter and creates a new node as
	environmental variables containing that string.
*/
t_ms_envar	*ms_env_newvar_def(char *envar_def)
{
	t_ms_envar	*new_envar;

	new_envar = malloc(sizeof(t_ms_envar));
	if (new_envar == NULL)
		return (NULL);
	ms_set_variable_name(new_envar, envar_def);
	ms_set_variable_content(new_envar, envar_def);
	new_envar->next = NULL;
	return (new_envar);
}

t_ms_envar	*ms_env_newvar_nc(char *name, char *content)
{
	//todo
	name = NULL;
	content = NULL;
	return (NULL);
}