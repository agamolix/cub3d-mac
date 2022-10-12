/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void calc_vertical(t_ray *ray)
{
	int height_wall;
	int wall_max;
	int wall_min;

	height_wall = WIN_HEIGHT / ray->distance;
	wall_max = WIN_HEIGHT / 2 - height_wall / 2;
	wall_min = WIN_HEIGHT / 2 + height_wall / 2;
	ray->vert_up = wall_max;
	ray->vert_down = wall_min;
}

void trace(t_img *img, t_data *data, t_ray *ray)
{
	int y;
	int color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y <= ray->vert_up)
			put_pix_on_img(img, ray->col, y, data->color_fc.color_c);
		else if (y > ray->vert_down)
			put_pix_on_img(img, ray->col, y, data->color_fc.color_f);
		else
		{
			if (ray->dir_nsew == 0)
				color = color_n(data, ray, y);
			else if (ray->dir_nsew == 1)
				color = color_s(data, ray, y);
			else if (ray->dir_nsew == 2)
				color = color_e(data, ray, y);
			else
				color = color_w(data, ray, y);
			put_pix_on_img(img, ray->col, y, color);
		}
		y++;
	}
}

void check_rays(t_img *img, t_data *data, t_ray *ray, t_player *player)
{
	double i;
	
	i = 0;
	while (i < WIN_WIDTH)
	{
		ray->pos_inside_cam = 2 * i / WIN_WIDTH - 1;
		ray->dir_x = player->dir_x + player->plane_x * ray->pos_inside_cam;
		ray->dir_y = player->dir_y + player->plane_y * ray->pos_inside_cam;
		calc_dist(data, ray, player);	
		calc_vertical(ray);
		trace(img, data, ray);
		ray->col += 1;
		i++;
	}
	ray->col = 0;
}
