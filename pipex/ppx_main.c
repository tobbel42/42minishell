/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:56:56 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/11 18:14:00 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	PIPEX MAIN
**	Error messages are printed in the subfunctions but exitpoint is only
**	in the main. except for argc check and the execution part.
*/
int	main(int argc, char **argv, char **envp)
{
	t_pipex		ppx;
	t_cmds		cmds;

	if (argc < 5)
	{
		write(2, \
		"Usage: ./pipex <infile> <cmd1> <cmd2> ... <cmdn> <outfile>\n", 60);
		pipex_free_and_exit(NULL, NULL, 1, EXIT_FAILURE);
	}
	if (check_and_set_fds(&ppx, argc, argv) != 0)
		pipex_free_and_exit(NULL, NULL, 1, EXIT_FAILURE);
	if (get_exec_paths(&ppx, envp) != 0)
		pipex_free_and_exit(&ppx, NULL, 1, EXIT_FAILURE);
	if (get_commands(&ppx, &cmds, argv, argc) != 0)
		pipex_free_and_exit(&ppx, &cmds, 1, EXIT_FAILURE);
	if (redirect_stdin_to_infile(&ppx) != 0)
		pipex_free_and_exit(&ppx, &cmds, 1, EXIT_FAILURE);
	execute_commands(&ppx, &cmds, envp);
	return (0);
}
