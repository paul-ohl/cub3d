/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:21:30 by pohl              #+#    #+#             */
/*   Updated: 2020/03/09 14:54:11 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "cub3d.h"

/*
** set_player_pos takes in a character of value 'N', 'S', 'E' or 'W' and sets
** the player's position using the line number (pos_x) and the width
** the function returns 0 in order to set the place where the player stands as
** an air block
*/

void	set_player_pos(t_config *config, char orientation, int pos_x)
{
	if (orientation == 'N')
		config->pl_angle = M_PI_2 * 3;
	else if (orientation == 'W')
		config->pl_angle = M_PI;
	else if (orientation == 'S')
		config->pl_angle = M_PI_2;
	else if (orientation == 'E')
		config->pl_angle = 0;
	config->pl_angle += 0.001;
	config->pl_pos.x = pos_x + 0.5;
	config->pl_pos.y = config->map_size.y - 0.5;
}

/*
** map_malloc copies the existing map array in a temp array if it exists,
** then creates another that is one unit longer and pastes the older array in
** returns 0 if everything goes well, -1 otherwise
*/

int		map_malloc(t_config *config)
{
	char	**temp;
	int		i;

	temp = config->map;
	if (!(config->map = malloc(sizeof(*temp) * (++config->map_size.y))))
		return (-1);
	i = 0;
	while (i < config->map_size.y - 1)
	{
		config->map[i] = temp[i];
		i++;
	}
	if (temp)
		free(temp);
	return (0);
}

/*
** check_config checks whether the rest of the parameters have been filled
** returns 0 if all the parameters have been filled
** returns -1 otherwise
*/

int		check_config(t_config *config)
{
	int		i;

	i = 0;
	if (config->c_col != -1 && config->f_col != -1 && config->res.x)
	{
		while (i < 5)
		{
			if (!(config->wall[i].ptr))
				return (-1);
			i++;
		}
		return (0);
	}
	return (-1);
}

int		read_line(t_config *config, char *line)
{
	int		i;
	int		width;

	i = -1;
	width = 0;
	while (line[++i])
	{
		if ((line[i] >= '0' && line[i] <= '2') || line[i] == ' ')
			config->map[config->map_size.y - 1][width++] =
					(line[i] == '1') ? 1 : line[i];
		else if (config->pl_angle == -1)
		{
			config->map[config->map_size.y - 1][width] = '0';
			set_player_pos(config, line[i], width++);
		}
		else if ((line[0] = 'P') == 'P')
			return (-1);
	}
	return (0);
}

/*
** read_map checks whether the rest of the parameters have been filled, then
** reads line in order to create a map in the format int**, and initialize the
** player's position and orientation.
** the function doesn't check the validity of the map's shape, only if the
** characters used are valid ('0' to '2', 'N', 'S', 'E' and 'W')
*/

int		read_map(t_config *config, char *line)
{
	int		width;
	char	*map_l;

	map_l = NULL;
	if (!config->map && check_config(config) && (line[0] = 'R') == 'R')
		return (-1);
	if (count_digits(line, &width) == -1 && (line[0] = 'W') == 'W')
		return (-1);
	if (map_malloc(config) || !(map_l = malloc(sizeof(*map_l) * width + 1)))
		return (-1);
	map_l[width] = -1;
	config->map[config->map_size.y - 1] = map_l;
	config->map_size.x = fmax(config->map_size.x, width);
	if (read_line(config, line))
		return (-1);
	return (0);
}
