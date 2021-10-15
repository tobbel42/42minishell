/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:19:02 by tgrossma          #+#    #+#             */
/*   Updated: 2021/07/05 14:30:15 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//returns the last element of lst
*/
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node;

	node = lst;
	if (node != NULL)
	{
		while (node->next != NULL)
			node = node->next;
	}
	return (node);
}
