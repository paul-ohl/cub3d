/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:59:59 by pohl              #+#    #+#             */
/*   Updated: 2020/02/23 18:25:08 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *str, size_t n)
{
	size_t			i;

	i = 0;
	while (n - i >= 8)
	{
		*((unsigned long long *)(str + i)) = (unsigned long long)0;
		i += 8;
	}
	if (n - i >= 4)
	{
		*((unsigned int *)(str + i)) = (unsigned int)0;
		i += 4;
	}
	if (n - i >= 2)
	{
		*((unsigned short *)(str + i)) = (unsigned short)0;
		i += 2;
	}
	if (n - i >= 1)
	{
		*((unsigned char *)(str + i)) = (unsigned char)0;
		i += 1;
	}
}
