/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:44:07 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/19 16:04:11 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../pipex/pipex.h"
# include "../lib_ms_tools/ms_tools.h"

typedef struct			s_ms_env_variable
{
	char						*all;
	char						*name;
	char						*content;
	struct s_ms_env_variable	*next;
}						t_ms_env_variable;

typedef struct s_ms_data
{
	char			*line;
	char			**exec_paths;
	char			**split_line;
	t_ms_env_variable	*env_vars_head;
}					t_ms_data;

//alice_functions

// env
int		ms_get_env(t_ms_data *ms, char **envp);
int		ms_env_add(t_ms_data *ms, char *env_variable);

// free
void	ms_free_and_exit(t_ms_data *ms, int exitflag, int exitstatus);
void	ms_free_env_list(t_ms_data *ms);
void	ms_free_char2(char **m);

// exec paths
int		ms_get_exec_paths(t_ms_data *ms);

// replace $
int	ms_replace_args(t_ms_data *ms);








//tobi_fuctions
int	ms_get_line(t_ms_data *ms_data);
int	ms_split(t_ms_data *ms_data);

















#endif
