/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wouf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohl <pohl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:36:24 by pohl              #+#    #+#             */
/*   Updated: 2020/03/09 20:22:25 by pohl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "cub3d.h"

void		get_hit_info(double vdir, double dist, double pos, t_object *object)
{
	double		hit_location;

	hit_location = dist / fabs(vdir)
			+ (vdir < 0 ? 1 - (pos - floor(pos)) : (pos - floor(pos)));
	hit_location = hit_location - floor(hit_location);
	hit_location = (vdir > 0) ? hit_location : 1 - hit_location;
	object->type = 1;
	object->hit_location = hit_location;
	object->distance = dist;
}

void		get_sprite_info(t_config *cfg, t_2int sprite_pos,
				int type, t_2double vdir)
{
	t_2double	cntr;
	t_object	*object;
	double		rel_angle;

	object = &cfg->list->obj[cfg->list->size++];
	object->face = 0;
	object->type = type;
	cntr = (t_2double){sprite_pos.x + 0.5, sprite_pos.y + 0.5};
	object->distance = hypot(cfg->pl_pos.x - cntr.x, cfg->pl_pos.y - cntr.y);
	rel_angle = (vdir.y > 0 ? 1 : -1) * acos(1 / vdir.x);
	rel_angle =
		rel_angle - atan2(cntr.y - cfg->pl_pos.y, cntr.x - cfg->pl_pos.x);
	object->hit_location = tan(rel_angle) * object->distance + .5;
	if (object->hit_location < 0 || object->hit_location > 1)
		object->hit_location = -1;
}

void		ray_movement(t_config *cfg, t_2int ray_p,
				t_2double vdir, t_2double dist)
{
	while (cfg->map[ray_p.y][ray_p.x] != 1)
	{
		if (dist.x < dist.y)
		{
			cfg->list->obj[cfg->list->size].face = (vdir.x > 0) ? 2 : 0;
			ray_p.x += (vdir.x < 0) ? -1 : 1;
			if (cfg->map[ray_p.y][ray_p.x] == 1 && cfg->list->size < MAX_OBJ)
				get_hit_info(vdir.y, dist.x, cfg->pl_pos.y,
					&cfg->list->obj[cfg->list->size++]);
			dist.x += fabs(vdir.x);
		}
		else
		{
			cfg->list->obj[cfg->list->size].face = (vdir.y > 0) ? 3 : 1;
			ray_p.y += (vdir.y < 0) ? -1 : 1;
			if (cfg->map[ray_p.y][ray_p.x] == 1 && cfg->list->size < MAX_OBJ)
				get_hit_info(vdir.x, dist.y, cfg->pl_pos.x,
					&cfg->list->obj[cfg->list->size++]);
			dist.y += fabs(vdir.y);
		}
		if (cfg->map[ray_p.y][ray_p.x] > 1 && cfg->list->size < MAX_OBJ)
			get_sprite_info(cfg, ray_p, cfg->map[ray_p.y][ray_p.x], vdir);
	}
}

void		ray(t_config *cfg, double angle)
{
	t_2int		ray_p;
	t_2double	vdir;
	t_2double	distance;

	vdir = (t_2double){1 / cos(angle), 1 / sin(angle)};
	ray_p = (t_2int){(int)cfg->pl_pos.x, (int)cfg->pl_pos.y};
	distance.x = (cfg->pl_pos.x - (int)cfg->pl_pos.x) * fabs(vdir.x);
	if (vdir.x > 0)
		distance.x = fabs(vdir.x) - distance.x;
	distance.y = (cfg->pl_pos.y - (int)cfg->pl_pos.y) * fabs(vdir.y);
	if (vdir.y > 0)
		distance.y = fabs(vdir.y) - distance.y;
	ray_movement(cfg, ray_p, vdir, distance);
}
