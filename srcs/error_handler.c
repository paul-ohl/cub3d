/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:44:40 by pohl              #+#    #+#             */
/*   Updated: 2020/05/09 16:37:42 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <mlx.h>

int		close_program(t_config *config)
{
	mlx_destroy_window(config->mlx_ptr, config->win_ptr);
	free_all(&config, 0);
	exit(1);
	return (0);
}

void	map_error(char *line)
{
	if (line[0] == 'R')
		ft_putstr_fd("Missing parameters.\n", 2);
	else if (line[0] == 'W')
		ft_putstr_fd("The map contains forbidden characters.\n", 2);
	else
		ft_putstr_fd("Map issue.\n", 2);
}

void	color_error(char *line)
{
	if (*line == 'F')
		ft_putstr_fd("Wrong formatting for the floor color parameter.\n", 2);
	else
		ft_putstr_fd("Wrong formatting for the ceiling color parameter.\n", 2);
}

void	tex_error(char *line)
{
	if (*line == 'N')
		ft_putstr_fd("The North texture is invalid.\n", 2);
	else if (*line == 'S' && line[1] == 'O')
		ft_putstr_fd("The South texture is invalid.\n", 2);
	else if (*line == 'E')
		ft_putstr_fd("The East texture is invalid.\n", 2);
	else if (*line == 'W')
		ft_putstr_fd("The West texture is invalid.\n", 2);
	else if (*line == 'S')
		ft_putstr_fd("The Sprite texture is invalid.\n", 2);
	else
		ft_putstr_fd("The identifier is invalid.\n", 2);
}

void	error(int code, t_config **config, char *line, int fd)
{
	ft_putstr_fd("Error\n", 2);
	if (code == 1)
		ft_putstr_fd("Invalid argument number.\n", 2);
	else if (code == 2)
		ft_putstr_fd("The resolution arguments are incorrect.\n", 2);
	else if (code == 3)
		tex_error(line);
	else if (code == 4)
		color_error(line);
	else if (code == 5)
		map_error(line);
	else if (code == 6)
		ft_putstr_fd("Invalid map\n", 2);
	else if (code == 7)
		ft_putstr_fd("The configuration file wasn't found, check path\n", 2);
	else if (code == 9)
		ft_putstr_fd("Wrong file type for the config file\n", 2);
	else
		ft_putstr_fd("unknown error\n", 2);
	if (line)
		free(line);
	free_all(config, fd);
	exit(1);
}
