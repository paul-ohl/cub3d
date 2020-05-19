/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:20:20 by pohl              #+#    #+#             */
/*   Updated: 2020/03/09 15:38:53 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

/*
** flood_fill is a recursive function that will check the validity of the map by
** trying to exit the map going from the player's position.
** if it manages to exit the map, the map is invalid and the function returns -1
** The function return 0 if the map is valid, i.e. it checked every space the
** player has access to and couldn't exit the map
*/

int		flood_fill(char **map, t_2int size, int x, int y)
{
	if (x == 0 || y == 0 || x == size.x - 1 || y == size.y - 1 ||
			map[y][x] == ' ')
		return (-1);
	map[y][x] -= '0';
	if (map[y - 1][x] > 9 && flood_fill(map, size, x, y - 1))
		return (-1);
	if (map[y + 1][x] > 9 && flood_fill(map, size, x, y + 1))
		return (-1);
	if (map[y][x - 1] > 9 && flood_fill(map, size, x - 1, y))
		return (-1);
	if (map[y][x + 1] > 9 && flood_fill(map, size, x + 1, y))
		return (-1);
	return (0);
}

int		normalize_map(t_config *config)
{
	char	*temp;
	int		i;
	int		line_length;

	i = 0;
	while (i < config->map_size.y)
	{
		line_length = 0;
		while (config->map[i][line_length] != -1)
			line_length++;
		if (line_length != config->map_size.x)
		{
			temp = config->map[i];
			if (!(config->map[i] = malloc(sizeof(*temp) * config->map_size.x)))
				return (-1);
			ft_memset(config->map[i], ' ', sizeof(*temp) * config->map_size.x);
			ft_memmove(config->map[i], temp, line_length);
			free(temp);
		}
		i++;
	}
	return (0);
}

int		check_map(t_config *config)
{
	t_2int	start_pos;

	start_pos.x = (int)floor(config->pl_pos.x);
	start_pos.y = (int)floor(config->pl_pos.y);
	if (normalize_map(config))
		return (-1);
	if (flood_fill(config->map, config->map_size, start_pos.x, start_pos.y))
		return (-1);
	return (0);
}
