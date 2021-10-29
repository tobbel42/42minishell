/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 09:53:42 by tgrossma          #+#    #+#             */
/*   Updated: 2021/07/19 12:50:40 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
//returns the position of c in string or the position of '\0' if c was not found
*/
int	gnl_find_char(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/*
//copys n bytes form src to dest, then NULL terminating dest
*/
void	gnl_strlcpy(char *dest, char *src, int n)
{
	int		i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

/*
//checks if both mallocs were successful, else frees any mallocations
*/
int	gnl_malloc_check(char *ptr1, char *ptr2)
{
	if (ptr1 && ptr2)
		return (1);
	else
	{
		if (ptr1)
			free(ptr1);
		if (ptr2)
			free(ptr2);
		return (0);
	}	
}

/*
//handels the cleanup, when an internal error in append line occurs
*/
int	gnl_read_cleanup(char *read_buf)
{
	free(read_buf);
	return (-1);
}
