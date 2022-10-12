/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void calc_ec_suiv(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->ec_x_suiv = 1000000;
	else	
		ray->ec_x_suiv = fabs(1 / ray->dir_x);
	if (ray->ec_y_suiv == 0)
		ray->ec_y_suiv = 1000000;
	else 
		ray->ec_y_suiv = fabs(1 / ray->dir_y);
}

void calc_ec(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
    {
		ray->ec_x_sens = -1;
		ray->ec_x = (player->x_double - player->x_int) * ray->ec_x_suiv;
    }
	else
	{
		ray->ec_x_sens = 1;
		ray->ec_x = (player->x_int + 1 - player->x_double) * ray->ec_x_suiv;
	}
	if (ray->dir_y < 0)
	{
		ray->ec_y_sens = -1;
		ray->ec_y = (player->y_double - player->y_int) * ray->ec_y_suiv;
	}
	else
	{
		ray->ec_y_sens = 1;
		ray->ec_y = (player->y_int + 1 - player->y_double) * ray->ec_y_suiv;
	}
}

void dist_loop(int stop, t_data *data, t_ray *ray)
{
	while(stop == 0)
	{
		if (ray->ec_x < ray->ec_y)
		{
			ray->ec_x += ray->ec_x_suiv;
			ray->player_line += ray->ec_x_sens;
			if (ray->dir_x <= 0)
				ray->dir_nsew = 0;
			else
				ray->dir_nsew = 1;
		}
		else
		{
			ray->ec_y += ray->ec_y_suiv;
			ray->player_col += ray->ec_y_sens;
			if (ray->dir_y <= 0)
				ray->dir_nsew = 2;
			else
				ray->dir_nsew = 3;
		}
		if(dval_map(data, ray->player_line, ray->player_col) == 1)
			stop = 1;
	}
}

void calc_dist(t_data *data, t_ray *ray, t_player *player)
{
	ray->player_line = player->x_int;
	ray->player_col = player->y_int;
	calc_ec_suiv(ray);
	calc_ec(ray, player);
	dist_loop(0, data, ray);
	if (ray->dir_nsew <= 1)
	{	
		ray->distance = ray->ec_x - ray->ec_x_suiv;
		ray->hit_wall_x = player->y_double + ray->distance * ray->dir_y;
		ray->hit_wall_x -= floor(ray->hit_wall_x);
		ray->hit_text_x = (int) (ray->hit_wall_x * (double)data->text_n.width);
	}
	else
	{
		ray->distance = ray->ec_y - ray->ec_y_suiv;
		ray->hit_wall_x = player->x_double + ray->distance * ray->dir_x;
		ray->hit_wall_x -= floor(ray->hit_wall_x);
		ray->hit_text_x = (int) (ray->hit_wall_x * (double)data->text_n.width); 
	}
}

