/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void populate_case_nswe(t_data *data, char c)
{
	data->player.start_pos = 1;	
	data->player.dir_x0 = data->player.dir_x;
	data->player.plane_x0 = data->player.plane_x;
	if (c == 'S')
	{
		data->player.dir_x = data->player.dir_x * cos(PI) - data->player.dir_y * sin(PI);
		data->player.dir_y = data->player.dir_x0 * sin(PI) + data->player.dir_y * cos(PI);
		data->player.plane_x = data->player.plane_x * cos(PI) - data->player.plane_y * sin(PI);
		data->player.plane_y = data->player.plane_x0 * sin(PI) + data->player.plane_y * cos(PI);
	}	
	else if (c == 'E')
	{
		data->player.dir_x = data->player.dir_x * cos(-1.570796327) - data->player.dir_y * sin(-1.570796327);
		data->player.dir_y = data->player.dir_x0 * sin(-1.570796327) + data->player.dir_y * cos(-1.570796327);
		data->player.plane_x = data->player.plane_x * cos(-1.570796327) - data->player.plane_y * sin(-1.570796327);
		data->player.plane_y = data->player.plane_x0 * sin(-1.570796327) + data->player.plane_y * cos(-1.570796327);
	}	
	else if (c == 'W')
	{
		data->player.dir_x = data->player.dir_x * cos(1.570796327) - data->player.dir_y * sin(1.570796327);
		data->player.dir_y = data->player.dir_x0 * sin(1.570796327) + data->player.dir_y * cos(1.570796327);
		data->player.plane_x = data->player.plane_x * cos(1.570796327) - data->player.plane_y * sin(1.570796327);
		data->player.plane_y = data->player.plane_x0 * sin(1.570796327) + data->player.plane_y * cos(1.570796327);
	}
}

void populate_map_cases(t_data *data, char *line, int i, int j)
{
	int element;

	element = 0;
	if (j < str_len(line) && line[j] == '1')
		element = 1;
	else if (j < str_len(line) && line[j] == '0')
		element = 0;
	else if (j < str_len(line) && (line[j] == ' ' || line[j] == '\n'))
		element = 2;
	else if (j < str_len(line) && (line[j] == 'N' || line[j] == 'S' || line[j] == 'E' || line[j] == 'W'))
	{	
		element = 0;
		data->player.x = i;
		data->player.y = j;
		populate_case_nswe(data, line[j]);
	}
	else if (j >= str_len(line))
		element = 2;
	else
		exit_error(data, "ERROR MAP: caractère non autorisé");
	data->map.coord[(i * data->map.nb_col + j)].line = i;
	data->map.coord[(i * data->map.nb_col + j)].col = j;
	data->map.coord[(i * data->map.nb_col + j)].value = element;
}

void	populate_map(t_data *data, t_map *map, int fd)
{
	int i = 0;
	int j = 0;
	char *line;
	int l = 0;

	while (i < map->nb_line)
	{
		line = get_next_line(fd);
		if (l >= map->start_line)
		{
			while (j < map->nb_col)
			{
				populate_map_cases(data, line, i, j);
				j++;
			}
			j = 0;
			i++;
		}
		l++;
	}
}
