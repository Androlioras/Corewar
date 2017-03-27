/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 04:24:02 by tdouge            #+#    #+#             */
/*   Updated: 2016/12/05 05:41:45 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **begin_list)
{
	t_list	*tmp_current;
	t_list	*tmp_prev;
	t_list	*tmp_next;

	tmp_prev = NULL;
	tmp_current = *begin_list;
	while (tmp_current)
	{
		tmp_next = tmp_current->next;
		tmp_current->next = tmp_prev;
		tmp_prev = tmp_current;
		tmp_current = tmp_next;
	}
	*begin_list = tmp_prev;
}
