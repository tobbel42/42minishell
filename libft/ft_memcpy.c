/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:57:55 by tgrossma          #+#    #+#             */
/*   Updated: 2021/06/28 13:57:55 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//copies the first n bytes of src to dest, returns pointer to dest
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptr1;
	char		*ptr2;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	ptr1 = (char *) src;
	ptr2 = (char *) dest;
	i = 0;
	while (i < n)
	{
		ptr2[i] = ptr1[i];
		i++;
	}
	return (dest);
}
