/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:02:15 by pohl              #+#    #+#             */
/*   Updated: 2019/10/17 18:28:04 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*buffer;
	unsigned int	s_len;

	i = 0;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	while (s[start + i])
		i++;
	if (s_len > start && ((buffer = (char *)malloc(1)) == NULL))
		return (NULL);
	else if (i >= len && ((buffer = (char *)malloc(len + 1)) == NULL))
		return (NULL);
	else if ((buffer = (char *)malloc(i + 1)) == NULL)
		return (NULL);
	i = 0;
	if (s_len > start)
		while (i < len && s[start + i])
		{
			buffer[i] = s[start + i];
			i++;
		}
	buffer[i] = 0;
	return (buffer);
}
