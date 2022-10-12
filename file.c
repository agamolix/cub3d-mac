/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_map(t_map *map, int fd)
{
	char *line;
	int max_col;
	int i;
	
	i = 0;
	map->nb_line = 0;
	map->nb_col = 0;
	while ((line = get_next_line(fd)) != 0)
	{
		if (i >= map->start_line)
		{
			max_col = str_len(line);
			if (map->nb_col < max_col)
				map->nb_col = max_col;
			map->nb_line++;
		}
		i++;
	}
	map->coord = malloc((map->nb_col * map->nb_line + 1) * sizeof(t_coord));
}

void verify_extern(t_data *data, t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (data->player.start_pos == 0)
		exit_error(data, "ERROR: pas de position pour le joueur");
	while (j < map->nb_col)
	{
		if (val_map(map, 0, j) == 0 || val_map(map, map->nb_line - 1, j) == 0)
			exit_error(data, "ERROR: map non fermée");
		j++;
	}
	while (i < map->nb_line)
	{
		if (val_map(map, i, 0) == 0 || val_map(map, i, map->nb_col - 1) == 0)
			exit_error(data, "ERROR: map non fermée");
		i++;
	}
}

void verify_intern(t_data *data, t_map *map)
{
	int i;
	int j;

	i = 1;
	j = 1;

	while (i < map->nb_line - 1)
	{
		while (j < map->nb_col - 1)
		{
			if (val_map(map, i, j) == 0 &&
			(val_map(map, i - 1, j) == 2 || val_map(map, i + 1, j) == 2 ||
			val_map(map, i, j - 1) == 2 || val_map(map, i, j + 1) == 2))
				exit_error(data, "ERROR: map non fermée");
			j++;
		}
		j = 1;
		i++;
	}
}

int open_file(t_data *data, t_map *map, char *path)
{
	int fd;
	
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_error(data, "ERROR: incorrect file .cub");
	parse(fd, data);
	close (fd);
	fd = open(path, O_RDONLY);
	calc_map(map, fd);
	close (fd);
	fd = open(path, O_RDONLY);
	populate_map(data, map, fd);
	verify_extern(data, map);
	verify_intern(data, map);
	close (fd);
	data->color_fc.color_c = get_color(data->color_fc.cr, data->color_fc.cg, data->color_fc.cb);
	data->color_fc.color_f = get_color(data->color_fc.fr, data->color_fc.fg, data->color_fc.fb);
	return (0);
}
