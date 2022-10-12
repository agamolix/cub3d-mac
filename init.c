/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_ray(t_data *data)
{
	data->ray.vert_up = 0;
	data->ray.vert_down = 0;
	data->ray.col = 0;
	data->ray.col = 0;
}

void modify_player(t_data *data)
{
	data->player.x += 0.5;
	data->player.y += 0.5;
	data->player.x_int = (int)data->player.x;
	data->player.y_int = (int)data->player.y;
	data->player.x_double = data->player.x;
	data->player.y_double = data->player.y;
}

void init_player(t_data *data)
{
	data->player.start_pos = 0;
	data->player.x = 2.5;
	data->player.y = 3.5;
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
}

void init_texture_fc(t_data *data)
{
	data->text_n.ok = 0;
	data->text_s.ok = 0;
	data->text_w.ok = 0;
	data->text_e.ok = 0;
	data->color_fc.cok = 0;
	data->color_fc.fok = 0;
}

void init(t_data *data, char *argv)
{
	init_player(data);
	init_texture_fc(data);
	char *path = argv;
	open_file(data, &data->map, path);
	modify_player(data);
	init_ray(data);
}
