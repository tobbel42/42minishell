#include "../header/minishell.h"

static char	*get_user(t_ms_data *ms_data)
{
	char	*user;

	user = NULL;
	if (ms_get_envar(ms_data, "USER") && ms_get_envar(ms_data, "USER")->content)
		user = ft_strdup(ms_get_envar(ms_data, "USER")->content);
	return (user);
}

static char	*get_pwd(t_ms_data *ms_data)
{
	char	*pwd;

	pwd = NULL;
	if (ms_get_envar(ms_data, "PWD") && ms_get_envar(ms_data, "PWD")->content
		&& ft_strrchr(ms_get_envar(ms_data, "PWD")->content, '/'))
		pwd = ft_strdup((ft_strrchr(
						ms_get_envar(ms_data, "PWD")->content, '/') + 1));
	return (pwd);
}

/*
//beautiful promt
*/
char	*ms_get_prompt(t_ms_data *ms_data)
{
	char	*user;
	char	*pwd;
	char	*promt;

	promt = NULL;
	user = get_user(ms_data);
	pwd = get_pwd(ms_data);
	if (user && pwd)
	{
		promt = ft_calloc(ft_strlen(user) + ft_strlen(pwd) + 6, sizeof(char));
		if (promt)
		{
			ft_strlcpy(promt, user, ft_strlen(user) + 2);
			promt[ft_strlen(user)] = '@';
			ft_strlcpy(promt + ft_strlen(user) + 1, pwd, ft_strlen(pwd) + 1);
			ft_strlcpy(promt + ft_strlen(user) + ft_strlen(pwd) + 1,
				" ༄  ", 7);
		}
	}
	if (user)
		free(user);
	if (pwd)
		free(pwd);
	return (promt);
}
