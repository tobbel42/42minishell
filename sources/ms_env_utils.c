#include "../header/minishell.h"

/*
	writes the environmental variables into a char** allocating memory for it.
	if allocation fails, null is returned.
*/
char	**ms_env_to_array(t_ms_data *ms)
{
	t_ms_envar	*curr;
	char		**env_arr;
	int			i;
	char		*tmp;

	curr = ms->envars_head;
	i = 0;
	env_arr = malloc(sizeof(char *) * (ms->env_lines_count + 1));
	if (!env_arr)
		return (NULL);
	while (curr != NULL)
	{
		tmp = ft_strjoin(curr->name, "=");
		env_arr[i] = ft_strjoin(tmp, curr->content);
		free(tmp);
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
void	ms_env_print(t_ms_data *ms, int fd)
{
	t_ms_envar	*curr;

	curr = ms->envars_head;
	while (curr != NULL)
	{
		write(fd, curr->name, ft_strlen(curr->name));
		write(fd, "=", 1);
		write(fd, curr->content, ft_strlen(curr->content));
		write(fd, "\n", 1);
		curr = curr->next;
	}
}

/*
	reverses the order of elements in the env list
*/
void	ms_env_reverse_list(t_ms_data *ms)
{
	t_ms_envar	*tmp;
	t_ms_envar	*rev_list_head;
	int			rev_list_size;

	rev_list_head = NULL;
	rev_list_size = 0;
	while (ms->envars_head != NULL)
	{
		tmp = ms->envars_head;
		ms->envars_head = ms->envars_head->next;
		tmp->next = rev_list_head;
		rev_list_head = tmp;
		rev_list_size++;
		ms->env_lines_count--;
	}
	ms->envars_head = rev_list_head;
	ms->env_lines_count = rev_list_size;
}

/*
	frees all allocated nodes of the environmental variables' list
	as long as head != NULL (-> if list empty, does nothing.)
*/
void	ms_env_free_list(t_ms_data *ms)
{
	t_ms_envar	*current;
	t_ms_envar	*tmp;

	current = ms->envars_head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		ms_env_free_envar(tmp);
		ms->env_lines_count--;
	}
}

/*
	Frees an environmental variable
*/
void	ms_env_free_envar(t_ms_envar *envar)
{
	if (envar->name != NULL)
		free(envar->name);
	if (envar->content != NULL)
		free(envar->content);
	free(envar);
}