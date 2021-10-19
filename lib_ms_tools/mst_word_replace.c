/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mst_word_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:15:24 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/19 15:55:48 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tools.h"

/*
	Replaces one word in a string with another, given the index of the start
	of the word to be replaced in the main string.
*/
char	*mst_word_replace(char *str, int start, char *del, char *repl)
{
	int		out_len;
	char	del_len;
	char	*out;
	int		i;
	int		j;

	del_len = ft_strlen(del);
	out_len = ft_strlen(str) - del_len + ft_strlen(repl);
	out = malloc(sizeof(char) * (out_len + 1));
	i = 0;
	while (i < start - 1)
	{
		out[i] = str[i];
		i++;
	}
	j = 0;
	while (repl[j] != '\0')
	{
		out[i + j] = repl[j];
		j++;
	}
	while (str[i + del_len + 1] != '\0')
	{
		out[i + j] = str[i + del_len + 1];
		i++;
	}
	return (out);
}
