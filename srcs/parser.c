/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:59:05 by pohl              #+#    #+#             */
/*   Updated: 2020/05/10 12:53:51 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include "cub3d.h"

void		free_all(t_config **conf, int fd)
{
	int	i;

	if (*conf)
	{
		if ((*conf)->mlx_ptr)
		{
			i = -1;
			while (++i < 5)
				if ((*conf)->wall[i].ptr)
					mlx_destroy_image((*conf)->mlx_ptr, (*conf)->wall[i].ptr);
			free((*conf)->mlx_ptr);
		}
		i = -1;
		while (++i < (*conf)->map_size.y)
			free((*conf)->map[i]);
		free((*conf)->map);
		if ((*conf)->list)
			free((*conf)->list);
		free(*conf);
		*conf = NULL;
		if (fd)
			close(fd);
	}
}

t_config	*initialize_config(void)
{
	t_config	*config;
	int			i;

	if ((config = malloc(sizeof(*config))))
	{
		ft_bzero(config, sizeof(config));
		i = 0;
		while (i < 5)
		{
			config->wall[i].ptr = 0;
			i++;
		}
		config->map = NULL;
		config->map_size = (t_2int){.x = 0, .y = 0};
		config->pl_angle = -1;
		config->f_col = -1;
		config->c_col = -1;
		config->res = (t_2int){.x = 0, .y = 0};
		if ((config->mlx_ptr = mlx_init()))
			return (config);
	}
	free_all(&config, 0);
	return (NULL);
}

int			analyse_line(char *line, t_config *config, int fd)
{
	int		i;

	i = 0;
	while (is_whitespace(line[i]))
		i++;
	if (line[i] == 'R' && read_res(config, line + i))
		error(2, &config, line, fd);
	else if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' ||
			line[i] == 'W') && read_tex(config, line + i))
		error(3, &config, line, fd);
	else if ((line[i] == 'F' || line[i] == 'C') && read_col(config, line + i))
		error(4, &config, line, fd);
	else if (line[i] >= '0' && line[i] <= '9' && read_map(config, line))
		error(5, &config, line, fd);
	return (0);
}

int			arg_processor(t_config *config, int argc, char **argv)
{
	int	i;
	int	fd;

	i = 0;
	if (argc < 2)
		error(1, &config, 0, 0);
	else if (argc > 3)
		error(1, &config, 0, 0);
	config->scrsht_on_start = 0;
	while (--argc > 0)
	{
		if (!ft_strcmp(argv[argc], "--save"))
			config->scrsht_on_start = 1;
		else
			fd = map_name_processor(config, argv[argc]);
	}
	return (fd);
}

int			main(int argc, char **argv)
{
	t_config	*config;
	int			i;
	int			fd;
	char		*line;

	if (!(config = initialize_config()))
		return (1);
	fd = arg_processor(config, argc, argv);
	while (get_next_line(fd, &line) > 0)
	{
		if (analyse_line(line, config, fd))
			return (1);
		free(line);
	}
	if (!(i = check_map(config)))
		cub3d(config);
	if (i)
		error(6, &config, line, fd);
	free(line);
	free_all(&config, fd);
	return (0);
}
