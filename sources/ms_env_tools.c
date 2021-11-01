#include "../header/minishell.h"

/*
	extrapolates the variable's name from its entry in env.
	If more than 1 '=', they et saved as 'content' from the second '='
	onwards.
*/
static void	ms_set_variable_name(t_ms_env_variable *variable)
{
	int	i;

	i = 0;
	if (variable->all == NULL)
	{
		variable->name = NULL;
		return ;
	}
	while (variable->all[i] != '\0')
	{
		if (variable->all[i] == '=')
			break ;
		i++;
	}
	variable->name = ft_substr(variable->all, 0, i);
}

/*
	extrapolates the variable's content from its entry in env
*/
static void	ms_set_variable_content(t_ms_env_variable *variable)
{
	int	i;
	int	strlen;
	int	empty_content;

	i = 0;
	empty_content = 1;
	if (variable->all == NULL)
	{
		variable->content = NULL;
		return ;
	}
	while (variable->all[i] != '\0')
	{
		if (variable->all[i] == '=')
		{
			empty_content = 0;
			break ;
		}
		i++;
	}
	strlen = ft_strlen(variable->all);
	if (empty_content == 0)
		variable->content = ft_substr(variable->all, i + 1, strlen - i - 1);
	else
		variable->content = NULL;
}

/*
	takes a string as parameter and creates a new node as
	environmental variables containing that string.
*/
t_ms_env_variable	*ms_env_new_variable(char *env_variable)
{
	t_ms_env_variable	*new_env_variable;

	new_env_variable = malloc(sizeof(t_ms_env_variable));
	if (new_env_variable == NULL)
		return (NULL);
	new_env_variable->all = ft_strdup(env_variable);
	ms_set_variable_name(new_env_variable);
	ms_set_variable_content(new_env_variable);
	new_env_variable->next = NULL;
	return (new_env_variable);
}

/*
	writes the environmental variables into a char** allocating memory for it.
	if allocation fails, null is returned.
*/
char	**ms_env_to_array(t_ms_data *ms)
{
	t_ms_env_variable	*curr;
	char				**env_arr;
	int					i;

	curr = ms->env_vars_head;
	i = 0;
	env_arr = malloc(sizeof(char *) * (ms->env_lines_count + 1));
	if (!env_arr)
		return (NULL);
	while (curr != NULL)
	{
		env_arr[i] = ft_strdup(curr->all);
		if (!env_arr[i])
		{
			ms_free_char2(env_arr);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

/*
	writes the env. variables' list to specified fd
*/
void	ms_print_env_list(t_ms_data *ms, int fd)
{
	t_ms_env_variable	*curr;

	curr = ms->env_vars_head;
	while (curr != NULL)
	{
		write(fd, curr->all, ft_strlen(curr->all));
		write(fd, "\n", 1);
		curr = curr->next;
	}
}
