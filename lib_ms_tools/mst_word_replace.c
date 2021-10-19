/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mst_word_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:15:24 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/19 20:07:00 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tools.h"
#include <stdio.h>

/*
	Replaces one word in a string with another, given the index of the start
	of the word to be replaced in the main string.
*/
char	*mst_word_replace(char *str, int start, char *del, char *repl)
{
	int		out_len;
	int		del_len;
	char	*out;
	int		i;
	int		j;

	// printf("from word replace function BEFORE: |%s|\n", str);
	// printf("from word replace function passed del: |%s|\n", del);
	// printf("from word replace function passed repl: |%s|\n", repl);
	del_len = ft_strlen(del);
	out_len = ft_strlen(str) - del_len + ft_strlen(repl);
	out = malloc(sizeof(char) * (out_len + 1));
	// printf("alloc len %d\n", out_len);
	// printf("alloc len %d\n", out_len);
	i = 0;
	while (i < start)
	{
		out[i] = str[i];
		i++;
	}
	// printf("from word replace function AFTER step 1: |%s|\n", out);
	j = 0;
	while (repl[j] != '\0')
	{
		out[i + j] = repl[j];
		j++;
	}
	// printf("from word replace function AFTER step 2: |%s|\n", out);
	while (str[i + del_len] != '\0')
	{
		out[i + j] = str[i + del_len];
		i++;
	}
	// printf("from word replace function FINAL: |%s|\n", out);
	return (out);
}
