/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:44:07 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/18 12:31:06 by akamlah          ###   ########.fr       */
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

typedef struct			s_ms_env_line
{
	char				*env_line;
	struct s_ms_env_line	*next;
}						t_ms_env_line;

typedef struct s_ms_data
{
	char			*line;
	char			**paths;
	t_ms_env_line	*env_head;
	t_pipex			*pipex;
}					t_ms_data;

//alice_functions

// env
int		ms_get_env(t_ms_data *ms, char **envp);
int		ms_env_add(t_ms_data *ms, char *env_line);

// free
void	ms_free_and_exit(t_ms_data *ms, int exitflag, int exitstatus);
void	ms_free_env_list(t_ms_data *ms);













//tobi_fuctions
int	ms_get_line(t_ms_data *ms_data);


















#endif
