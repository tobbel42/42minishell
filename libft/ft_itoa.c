/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:32:14 by tgrossma          #+#    #+#             */
/*   Updated: 2021/06/30 15:36:47 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_len(int n)
{
	int		i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	itoa_fill(char *ptr, int n, int len)
{
	int		i;

	i = 1;
	if (n >= 0)
	{
		while (i <= len)
		{
			ptr[len - i] = (n % 10 + 48);
			n = n / 10;
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			ptr[len - i] = ((n % 10) * (-1) + 48);
			n = n / 10;
			i++;
		}
		ptr[0] = '-';
	}
}

/*
//transforms the integer to a string
//returns NULL on error
*/
char	*ft_itoa(int n)
{	
	char	*ptr;
	int		len;

	len = itoa_len(n);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (ptr);
	ptr[len] = '\0';
	itoa_fill(ptr, n, len);
	return (ptr);
}
