/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:51:07 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/14 20:54:28 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	void *tmp;

	while (*alst)
	{
		tmp = (*alst)->next;
		ft_lstdelone(alst, del);
		(*alst) = tmp;
	}
	*alst = NULL;
}
