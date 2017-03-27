/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:12:40 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/14 22:40:35 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_list;

	new_list = NULL;
	if (lst && f)
	{
		new_list = (*f)(lst);
		if (new_list && lst->next)
			new_list->next = ft_lstmap(lst->next, f);
	}
	return (new_list);
}
