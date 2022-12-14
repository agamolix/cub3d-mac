/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/16 13:49:32 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_pos(t_data *data, t_player *p, double ang)
{
	p->dir_x = p->dir_x * cos(ang) - p->dir_y * sin(ang);
	p->dir_y = p->dir_x0 * sin(ang) + p->dir_y * cos(ang);
	p->plane_x = p->plane_x * cos(ang) - p->plane_y * sin(ang);
	p->plane_y = p->plane_x0 * sin(ang) + p->plane_y * cos(ang);
}

void	populate_case_nswe(t_data *data, char c)
{
	data->player.start_pos = 1;
	data->player.dir_x0 = data->player.dir_x;
	data->player.plane_x0 = data->player.plane_x;
	if (c == 'S')
		set_player_pos(data, &data->player, PI);
	else if (c == 'E')
		set_player_pos(data, &data->player, -1.570796327);
	else if (c == 'W')
		set_player_pos(data, &data->player, 1.570796327);
}

void	check_and_set_player(t_data *data, int i, int j)
{
	if (data->player.x || data->player.y)
		exit_error(data, "Error: Only one player position allowed");
	data->player.x = i;
	data->player.y = j;
}

void	populate_map_cases(t_data *data, char *line, int i, int j)
{
	int	element;

	element = 0;
	if (j < str_len(line) && line[j] == '1')
		element = 1;
	else if (j < str_len(line) && line[j] == '0')
		element = 0;
	else if (j < str_len(line) && (line[j] == ' ' || line[j] == '\n'))
		element = 2;
	else if (j < str_len(line) && (line[j] == 'N' || line[j] == 'S' \
								|| line[j] == 'E' || line[j] == 'W'))
	{	
		element = 0;
		check_and_set_player(data, i, j);
		populate_case_nswe(data, line[j]);
	}
	else if (j >= str_len(line))
		element = 2;
	else
		exit_error(data, "ERROR: map");
	data->map.coord[(i * data->map.nb_col + j)].line = i;
	data->map.coord[(i * data->map.nb_col + j)].col = j;
	data->map.coord[(i * data->map.nb_col + j)].value = element;
}

void	populate_map(t_data *data, t_map *map, int fd)
{
	int		i;
	int		j;
	char	*line;
	int		l;

	l = 0;
	j = 0;
	i = 0;
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
		if (line)
			free(line);
		l++;
	}
}
