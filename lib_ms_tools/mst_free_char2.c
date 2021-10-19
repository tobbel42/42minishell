/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mst_free_char2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:54:23 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/19 15:54:52 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tools.h"

/*
** Frees an array of pointers to string
*/
void	mst_free_char2(char **m)
{
	int	i;

	i = 0;
	while (m[i] != NULL)
	{
		free(m[i]);
		m[i] = NULL;
		i++;
	}
	if (m != NULL)
		free(m);
		
}
