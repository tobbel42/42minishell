/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:57:58 by tgrossma          #+#    #+#             */
/*   Updated: 2021/06/28 13:57:58 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//copies n bytes from dest to src, the areas may overlap
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	char		*src_ptr;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	dest_ptr = (char *) dest;
	src_ptr = (char *) src;
	i = 0;
	while (i < n)
	{
		if (dest_ptr > src_ptr)
			dest_ptr[n - 1 - i] = src_ptr[n - 1 - i];
		else
			dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}
