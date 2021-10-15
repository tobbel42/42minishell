/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:34:53 by tgrossma          #+#    #+#             */
/*   Updated: 2021/07/05 17:01:51 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//applies the function ’f’ to the content of each element. Creates a new
//list resulting of the successive applications of the function ’f’. 
//The ’del’ function is used to delete the content of an element if needed.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;

	if (!lst)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (new_list == NULL)
		return (NULL);
	lst = lst->next;
	new_node = new_list;
	while (lst)
	{
		new_node->next = ft_lstnew(f(lst->content));
		if (new_node->next == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		lst = lst->next;
		new_node = new_node->next;
	}
	return (new_list);
}
