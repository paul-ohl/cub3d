/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:28:39 by pohl              #+#    #+#             */
/*   Updated: 2019/10/12 17:39:01 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last_elt;

	last_elt = *alst;
	while (last_elt && last_elt->next)
	{
		last_elt = last_elt->next;
	}
	if (last_elt)
		last_elt->next = new;
	else
		*alst = new;
}
