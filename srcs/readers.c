/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:39:07 by pohl              #+#    #+#             */
/*   Updated: 2020/05/10 12:53:19 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <X11/Xlib.h>

/*
** read_res reads the two arguments given for resolution and returns -1 if
** there are not enough arguments, too many, or if they are not valid
** If the data is valid, saves the resolution in config
*/

int		read_res(t_config *cfg, char *line)
{
	int		i;
	int		temp;
	t_2int	sc;

	mlx_get_screen_size(cfg->mlx_ptr, &(sc.x), &(sc.y));
	cfg->res.x = 0;
	cfg->res.y = 0;
	i = 1;
	temp = ft_atoi_increment(line, &i);
	cfg->res.x = (cfg->scrsht_on_start || temp < sc.x) ? temp : sc.x;
	if (line[i])
	{
		temp = ft_atoi_increment(line, &i);
		cfg->res.y = (cfg->scrsht_on_start || temp < sc.y) ? temp : sc.y;
		if (cfg->res.x > 0 && cfg->res.y > 0)
		{
			i--;
			while (line[++i])
				if (!is_whitespace(line[i]))
					return (-1);
			return (0);
		}
	}
	return (-1);
}

/*
** read_col reads the three arguments given for the color and returns -1 if
** there are not enough arguments, too many, or if they are not valid
** If the data is valid, saves the color value in the corresponding color in
** config.
*/

int		read_col(t_config *config, char *line)
{
	int		i;
	int		counter;
	int		color;
	int		temp;

	color = 0;
	i = 1;
	counter = 2;
	while (counter >= 0)
	{
		temp = ft_atoi_increment(line, &i);
		if (temp > 255 || temp < 0 || (temp == 0 && line[i - 1] != '0'))
			return (-1);
		color = color | (temp << (counter * 8));
		while (line[i] && is_whitespace(line[i]) && line[i] != ',')
			i++;
		if (counter && (i++) != -1 && line[i - 1] != ',')
			return (-1);
		if (!counter-- && line[i])
			return (-1);
	}
	color &= 0x00ffffff;
	if (*line == 'C' || (config->f_col = color) == -1)
		config->c_col = color;
	return (0);
}

int		check_code(char *line)
{
	if (((line[0] == 'N' && line[1] == 'O') || (line[0] == 'S'
			&& line[1] == 'O') || (line[0] == 'E' && line[1] == 'A')
			|| (line[0] == 'W' && line[1] == 'E'))
			&& is_whitespace(line[2]))
		return (0);
	if (line[0] == 'S' && is_whitespace(line[1]))
		return (0);
	line[0] = 'I';
	return (1);
}

void	assign_texture(t_config *config, t_texture tex, char *line)
{
	if (*line == 'N' && line[1] == 'O')
		config->wall[3] = tex;
	else if (*line == 'S' && line[1] == 'O')
		config->wall[1] = tex;
	else if (*line == 'E' && line[1] == 'A')
		config->wall[0] = tex;
	else if (*line == 'W' && line[1] == 'E')
		config->wall[2] = tex;
	else
		config->wall[4] = tex;
}

/*
** read_tex reads the path to a texture, checks whether it is valid or not
** and if it is, stores it in the t_texture format under the corresponding
** index of wall in config. wall[4] is the texture for the sprite.
*/

int		read_tex(t_config *config, char *line)
{
	int			i;
	int			bpp;
	t_texture	tex;

	if (check_code(line))
		return (-1);
	i = 2;
	while (is_whitespace(line[i]))
		i++;
	tex.ptr = mlx_xpm_file_to_image(config->mlx_ptr, line + i,
			&tex.size.x, &tex.size.y);
	tex.size.y--;
	if (!tex.ptr)
		return (-1);
	tex.data = (int *)mlx_get_data_addr(tex.ptr, &bpp, &tex.sl, &i);
	tex.sl /= 4;
	assign_texture(config, tex, line);
	return (0);
}
