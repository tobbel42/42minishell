/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:56:52 by tgrossma          #+#    #+#             */
/*   Updated: 2021/06/28 13:56:52 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//set n bytes starting from s to zero
*/
void	ft_bzero(void *s, size_t n)
{
	size_t		counter;
	char		*ptr;

	counter = 0;
	ptr = (char *)s;
	while (counter < n)
	{
		ptr[counter] = 0;
		counter++;
	}
}
