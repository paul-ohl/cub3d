/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:45:21 by pohl              #+#    #+#             */
/*   Updated: 2020/05/03 12:17:21 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>

#define ARR_LEFT 65361
#define ARR_RIGHT 65363
#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100
#define ESC 65307

#define SPEED 0.051

int		move(int keycode, t_config *config)
{
	if (keycode == UP && !config->mvt_forward)
		config->mvt_forward = 1;
	if (keycode == DOWN && !config->mvt_forward)
		config->mvt_forward = -1;
	if (keycode == LEFT && !config->mvt_side)
		config->mvt_side = 1;
	if (keycode == RIGHT && !config->mvt_side)
		config->mvt_side = -1;
	if (keycode == ARR_LEFT)
		config->rot -= 1;
	if (keycode == ARR_RIGHT)
		config->rot += 1;
	if (keycode == 116)
		if (create_img(config->res.x, config->res.y, config->img.data))
			close_program(config);
	mlx_loop_hook(config->mlx_ptr, &display, config);
	return (1);
}

int		stop_move(int keycode, t_config *config)
{
	if (keycode == UP || keycode == DOWN)
		config->mvt_forward = 0;
	if (keycode == LEFT || keycode == RIGHT)
		config->mvt_side = 0;
	if (keycode == ARR_LEFT || keycode == ARR_RIGHT)
		config->rot = 0;
	if (keycode == ESC)
		close_program(config);
	if (!(config->mvt_side || config->mvt_forward || config->rot))
		mlx_loop_hook(config->mlx_ptr, (void*)0, 0);
	return (1);
}

void	apply_movement(t_config *config)
{
	double	speed;
	double	new_pos_x;
	double	new_pos_y;

	speed = SPEED;
	new_pos_x = config->pl_pos.x;
	new_pos_y = config->pl_pos.y;
	if (config->mvt_forward)
	{
		new_pos_x += cos(config->pl_angle) * speed * config->mvt_forward;
		new_pos_y += sin(config->pl_angle) * speed * config->mvt_forward;
	}
	if (config->mvt_side)
	{
		new_pos_x += cos(config->pl_angle - M_PI_2) * speed * config->mvt_side;
		new_pos_y += sin(config->pl_angle - M_PI_2) * speed * config->mvt_side;
	}
	if (config->map[(int)floor(config->pl_pos.y)][(int)floor(new_pos_x)] != 1)
		config->pl_pos.x = new_pos_x;
	if (config->map[(int)floor(new_pos_y)][(int)floor(config->pl_pos.x)] != 1)
		config->pl_pos.y = new_pos_y;
	if (config->rot > 0)
		config->pl_angle += M_PI / 64;
	else if (config->rot < 0)
		config->pl_angle -= M_PI / 64;
}
