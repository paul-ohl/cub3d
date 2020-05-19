/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:41:39 by pohl              #+#    #+#             */
/*   Updated: 2020/05/10 12:53:51 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "cub3d.h"

void	reset_screen(int32_t *img_data, int sl, t_config *config, int screen_x)
{
	int		i;

	i = 0;
	while (i < (config->res.y / 2))
	{
		img_data[i * sl + screen_x] = config->c_col;
		i++;
	}
	while (i < config->res.y)
	{
		img_data[i * sl + screen_x] = config->f_col;
		i++;
	}
}

void	draw_column(t_config *conf, t_obj_list *list, int col)
{
	int		pixel;
	int		i;
	int		draw_line;
	int		tex_height;

	while (list->size--)
	{
		draw_line = (int)(conf->res.y / (list->obj[list->size].distance *
			((list->obj[list->size].type > 1) ? 1 : cos(conf->angles[col])))) *
			conf->res.x / conf->res.y;
		tex_height = draw_line;
		if (draw_line > conf->res.y)
			draw_line = conf->res.y;
		i = -draw_line / 2;
		while (i < draw_line / 2)
		{
			pixel = col + (conf->res.y / 2 + i) * conf->img.sl;
			conf->img.data[pixel] = merge(darken(get_tex(conf, i, tex_height,
				&list->obj[list->size]), list->obj[list->size].distance),
				conf->img.data[pixel]);
			i++;
		}
	}
}

int		display(t_config *cfg)
{
	int			i;

	apply_movement(cfg);
	i = 0;
	while (i < cfg->res.x)
	{
		cfg->list->size = 0;
		reset_screen(cfg->img.data, cfg->img.sl, cfg, i);
		ray(cfg, cfg->pl_angle + cfg->angles[i]);
		draw_column(cfg, cfg->list, i);
		i++;
	}
	if (cfg->scrsht_on_start)
		create_img(cfg->res.x, cfg->res.y, cfg->img.data);
	else
		mlx_put_image_to_window(cfg->mlx_ptr, cfg->win_ptr, cfg->img.ptr, 0, 0);
	return (1);
}

double	*ray_angles_calculator(double fov, int screen_width)
{
	double	virtual_width;
	double	ratio;
	double	*angle_table;
	int		i;

	if (!(angle_table = malloc(sizeof(*angle_table) * screen_width)))
		return (NULL);
	virtual_width = fov / M_PI_2;
	i = 0;
	while (i < screen_width)
	{
		ratio = i / (double)screen_width - 0.5;
		angle_table[i] = atan(ratio * virtual_width);
		i++;
	}
	return (angle_table);
}

int		cub3d(t_config *conf)
{
	int		u;

	if (!(conf->list = malloc(sizeof(*conf->list))))
		return (-1);
	conf->img.ptr = mlx_new_image(conf->mlx_ptr, conf->res.x, conf->res.y);
	if (!conf->img.ptr)
		return (-1);
	conf->angles = ray_angles_calculator(M_PI_2, conf->res.x);
	conf->img.data = (int *)mlx_get_data_addr(conf->img.ptr, &u,
			&conf->img.sl, &u);
	conf->img.sl /= 4;
	if (conf->scrsht_on_start)
		return (display(conf));
	if (!(conf->win_ptr = mlx_new_window(conf->mlx_ptr,
			conf->res.x, conf->res.y, "Not DOOM")))
		return (-1);
	mlx_do_key_autorepeatoff(conf->mlx_ptr);
	mlx_expose_hook(conf->win_ptr, &display, conf);
	mlx_hook(conf->win_ptr, 2, 1 << 0, &move, conf);
	mlx_hook(conf->win_ptr, 3, 1 << 1, &stop_move, conf);
	mlx_hook(conf->win_ptr, 17, 1 << 17, &close_program, conf);
	display(conf);
	mlx_loop(conf->mlx_ptr);
	return (1);
}
