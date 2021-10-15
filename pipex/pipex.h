/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:56:04 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/15 14:41:28 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>

# define TRUE	1
# define FALSE	0

typedef struct s_command
{
	char				**args;
	struct s_command	*next;
}						t_command;

typedef struct s_cmds
{
	t_command	*head;
	int			size;
}				t_cmds;

typedef struct s_pipex
{
	int			fd[2];
	int			infile_fd;
	int			outfile_fd;
	int			pid;
	int			output_fd;
	char		**exec_paths;
	char		*infile;
	char		*outfile;
}				t_pipex;

// get exec paths (+2 static utils)
int		get_exec_paths(t_pipex *ppx, char **envp);

// files
int		check_and_set_fds(t_pipex *ppx, int argc, char **argv);
int		redirect_stdin_to_infile(t_pipex *ppx);

// parse commands (+2 static utils)
int		get_commands(t_pipex *ppx, t_cmds *cmds, char **argv, int argc);

// cmd utils
int		is_valid_cmd_path(char *path);
void	reverse_commands_list(t_cmds *cmds);
int		add_command_to_list(t_cmds *cmds, char **args);
void	cmds_init(t_cmds *cmds);
void	write_command_not_found(char *cmd_name);

// exec (+4 static functinalities)
void	execute_commands(t_pipex *ppx, t_cmds *cmds, char **envp);

// exit and free
void	pipex_free_and_exit(t_pipex *ppx, t_cmds *cmds, int extflg, int status);
void	free_pipex_data(t_pipex *ppx);
void	free_commands_list(t_cmds *cmds);
void	free_command(t_command *cmd);
void	pipex_exit(int exitstatus);

// lft additions
void	ft_free_char2(char **m);
char	*ft_get_first_word(char *str);

#endif