/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 13:21:11 by tgrossma          #+#    #+#             */
/*   Updated: 2021/07/16 13:04:33 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//allocates count blocks of size and set the memory to zero
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	max;

	max = count * size;
	ptr = malloc(max);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, max);
	return (ptr);
}
