/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:16:30 by pohl              #+#    #+#             */
/*   Updated: 2019/10/15 10:55:32 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void *content)
{
	t_list	*new_element;

	if ((new_element = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	new_element->next = NULL;
	new_element->content = content;
	return (new_element);
}
