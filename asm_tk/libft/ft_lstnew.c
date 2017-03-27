/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 12:14:28 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/14 20:55:45 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	void		*i;
	t_list		*new_elem;

	i = NULL;
	if (!(i = malloc(content_size)))
		return (NULL);
	if (content == NULL)
	{
		i = 0;
		content_size = 0;
	}
	if (!(new_elem = malloc(sizeof(t_list))))
		return (NULL);
	else
		i = ft_memcpy(i, content, content_size);
	new_elem->content = i;
	new_elem->content_size = content_size;
	new_elem->next = NULL;
	return (new_elem);
}
