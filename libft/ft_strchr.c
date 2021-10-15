/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:58:32 by tgrossma          #+#    #+#             */
/*   Updated: 2021/06/28 13:58:32 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//returns a pointer to the first occurence of c in string s
*/
char	*ft_strchr(const char *s, int c)
{
	size_t		i;

	i = 0;
	while (s[i] != 0 && s[i] != c)
		i++;
	if (s[i] == c)
		return ((char *)(s + i));
	return (0);
}
