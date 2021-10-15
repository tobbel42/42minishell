/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:58:01 by tgrossma          #+#    #+#             */
/*   Updated: 2021/06/28 13:58:01 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//fills the first n bytes of memarea pointed to by s with the constant byte c
*/
void	*ft_memset(void *s, int c, size_t n)
{
	size_t		counter;
	char		*ptr;

	ptr = (char *) s;
	counter = 0;
	while (counter < n)
	{
		ptr[counter] = c;
		counter++;
	}
	return (s);
}
