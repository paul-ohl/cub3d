/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:23:38 by pohl              #+#    #+#             */
/*   Updated: 2019/10/11 12:31:47 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	free_mallocs(char **buffer, int *size)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
	free(size);
	return (0);
}

static int	ft_nbword(char const *s, char c)
{
	int i;
	int nbword;

	i = 0;
	nbword = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i - 1] == c) || (s[i] != c && i == 0))
			nbword++;
		i++;
	}
	return (nbword);
}

static int	*fill_size(char const *s, char c)
{
	int i;
	int j;
	int *size;
	int nbword;

	i = 0;
	nbword = ft_nbword(s, c);
	if (!(size = malloc(sizeof(int) * nbword)))
		return (NULL);
	while (i <= nbword)
	{
		size[i] = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
			size[j]++;
		else if (i > 0 && s[i - 1] != c)
			j++;
		i++;
	}
	return (size);
}

static int	create_tab(char const *s, char c, char **tab, int *size)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			if (i == 0 || (s[i] != c && s[i - 1] == c))
				if (!(tab[j] = malloc(sizeof(char) * (size[j] + 1))))
					return (free_mallocs(tab, size));
			tab[j][k] = s[i];
			tab[j][++k] = '\0';
		}
		else if (i > 0 && s[i - 1] != c && ++j)
			k = 0;
	}
	return (1);
}

char		**ft_split(char const *s, char c)
{
	char	**tab;
	int		*size;

	if (!(tab = malloc(sizeof(char *) * (ft_nbword(s, c) + 1))))
		return (NULL);
	size = fill_size(s, c);
	if (!create_tab(s, c, tab, size))
		return (NULL);
	free(size);
	tab[(ft_nbword(s, c))] = 0;
	return (tab);
}
