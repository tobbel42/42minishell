/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 12:23:41 by tgrossma          #+#    #+#             */
/*   Updated: 2021/07/05 12:31:21 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
//creates a new list element with content content
*/
t_list	*ft_lstnew(void	*content)
{
	t_list	*new_e;

	new_e = malloc(sizeof(t_list));
	if (new_e == NULL)
		return (NULL);
	new_e->content = content;
	new_e->next = NULL;
	return (new_e);
}
