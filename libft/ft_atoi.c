/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:56:22 by tgrossma          #+#    #+#             */
/*   Updated: 2021/06/28 13:56:22 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//convertes a string into an integer
//does not check for over/underflow
*/
int	ft_atoi(const char *nptr)
{
	int		i;
	int		n;
	int		sign_flag;

	n = 0;
	i = 0;
	sign_flag = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		sign_flag = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		n = (n * 10) + (nptr[i] - 48);
		i++;
	}
	return (n * sign_flag);
}
