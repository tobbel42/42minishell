/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:59:14 by tgrossma          #+#    #+#             */
/*   Updated: 2021/06/28 13:59:14 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//returns a substring of s, starting on index start and at max len bytes
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		strlen;
	char		*ptr;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start > strlen)
	{
		ptr = (char *)ft_calloc(1, 1);
		return (ptr);
	}
	strlen = strlen - start;
	if (len < strlen)
		strlen = len;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, &s[start], len);
	ptr[len] = '\0';
	return (ptr);
}
