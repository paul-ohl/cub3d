/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:52:52 by pohl              #+#    #+#             */
/*   Updated: 2020/02/23 19:51:24 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

char		*ft_strjoin_freefirst(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			i++;
	if (s2)
		while (s2[j])
			j++;
	if ((buffer = (char *)malloc(i + j + 1)) == NULL)
		return (NULL);
	if (s1 && (j = -1))
		while (s1[++j])
			buffer[j] = s1[j];
	if (s2 && (j = -1))
		while (s2[++j])
			buffer[i + j] = s2[j];
	buffer[i + j] = 0;
	if (s1)
		free((void *)s1);
	return (buffer);
}

char		*ft_strncpy(char *dst, const char *src, int len)
{
	int i;

	if (dst == NULL && src == NULL)
		return (0);
	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

static int	check_rest(char **rest, char **line)
{
	long n;
	char *temp;

	if (*rest && (n = ft_strchr(*rest, '\n') - *rest) >= 0)
	{
		if ((*line = (char *)malloc(sizeof(**line) * (n + 1))))
		{
			ft_strncpy(*line, *rest, n);
			if ((temp = ft_strdup(*rest + n + 1)))
			{
				free(*rest);
				*rest = temp;
				return (1);
			}
		}
		return (-1);
	}
	if (!*rest)
	{
		if (!(*rest = (char *)malloc(sizeof(**rest))))
			return (-1);
		(*rest)[0] = 0;
	}
	return (0);
}

int			final_return(char **line, char **rest)
{
	if (rest)
	{
		*line = ft_strdup(*rest);
		free(*rest);
		*rest = 0;
		if (*line)
			return (0);
	}
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	static char	*rest = NULL;
	int			n;
	char		*temp;

	if (read(fd, 0, 0) == -1 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((n = check_rest(&rest, line)) == 0)
	{
		if (!(temp = (char *)malloc(sizeof(*temp) * BUFFER_SIZE + 1)))
			return (-1);
		if ((n = read(fd, temp, BUFFER_SIZE)) > 0)
		{
			temp[n] = 0;
			if (!(rest = ft_strjoin_freefirst(rest, temp)))
				free(temp);
			if (!rest)
				return (-1);
		}
		free(temp);
		if (n == 0)
			return (final_return(line, &rest));
		if (n < 0)
			return (-1);
	}
	return (n);
}
