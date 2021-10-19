/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mst_isequal_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:44:23 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/19 15:49:09 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_tools.h"

int	mst_isequal_str(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if ((ft_strnstr(s1, s2, len1) != NULL) && (len1 == len2))
		return (1);
	return (0);
}
