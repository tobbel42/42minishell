/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:58:52 by tgrossma          #+#    #+#             */
/*   Updated: 2021/06/29 18:23:55 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//applies the function f to each char of string s, returns the result
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{	
	char			*ptr;
	unsigned int	len;
	unsigned int	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	i = 0;
	while (i < len)
	{
		ptr[i] = (f)(i, s[i]);
		i++;
	}
	return (ptr);
}
