/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:07:18 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/11 18:00:20 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	FILES PARSER
**	Checks if infile is readable and if so open a file descriptor to it.
**	Then checks if filename for outfile passed, and if so a fd to it is
**	opened.
*/
int	check_and_set_fds(t_pipex *ppx, int argc, char **argv)
{
	ppx->infile = argv[1];
	ppx->infile_fd = open(ppx->infile, O_RDONLY);
	if (ppx->infile_fd < 0)
	{
		perror(ppx->infile);
		close(ppx->infile_fd);
		return (-1);
	}
	ppx->outfile = argv[argc - 1];
	ppx->outfile_fd = open(ppx->outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (ppx->outfile_fd < 0)
	{
		perror(ppx->outfile);
		close(ppx->infile_fd);
		return (-1);
	}
	return (0);
}

/*
**	Redirects the stdin to the infile fd. Returns error if redirection failed.
*/
int	redirect_stdin_to_infile(t_pipex *ppx)
{
	if (dup2(ppx->infile_fd, STDIN_FILENO) == -1)
	{
		perror("Redirection of stdin to infile:");
		return (-1);
	}
	close(ppx->infile_fd);
	return (0);
}
