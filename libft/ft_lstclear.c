/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:14:35 by tgrossma          #+#    #+#             */
/*   Updated: 2021/07/05 15:29:37 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//Deletes and frees the given element and every successor of that element,
//using the function ’del’ and free, the pointer to the list is set to NULL.
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*nxt_node;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		nxt_node = node->next;
		ft_lstdelone(node, del);
		node = nxt_node;
	}
	*lst = NULL;
}
