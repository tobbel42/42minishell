/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mst_get_next_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:49:33 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/19 15:50:07 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mstools.h"

/*
** Returns the next word after a pointer to char
*/
char	*mst_get_next_word(char *str)
{
	char	*word;
	int		i;

	i = 0;
	while (ft_isspace(str[i]) != 1 && str[i] != '\0')
		i++;
	word = ft_substr(str, 0, i);
	return (word);
}
