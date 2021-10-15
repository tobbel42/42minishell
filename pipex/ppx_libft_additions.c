/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_libft_additions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:26:16 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/15 14:29:21 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Returns first word of a string
*/
char	*ft_get_first_word(char *str)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	word = ft_substr(str, 0, i);
	return (word);
}

/*
** Frees an array of pointers to string
*/
void	ft_free_char2(char **m)
{
	int	i;

	i = 0;
	while (m[i] != NULL)
	{
		free(m[i]);
		i++;
	}
	if (m != NULL)
		free(m);
}
