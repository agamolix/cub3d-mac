/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/10/11 17:21:55 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int color_n(t_data *data, t_ray *ray, int y)
{
	int pos_x;
	double pct;
	int pos_y;
	int pos;
	int color;

	pos_x = data->ray.hit_text_x;
	pct = (double)(y - ray->vert_up) / (ray->vert_down - ray->vert_up);
	pos_y = pct * data->text_e.width;
	pos = (pos_y * data->text_n.line_len + pos_x * data->text_n.bpp / 8);
	color = get_color_inv(data->text_n.addr[pos], data->text_n.addr[pos + 1], data->text_n.addr[pos + 2]);
	return(color);
}

int color_s(t_data *data, t_ray *ray, int y)
{
	int pos_x;
	double pct;
	int pos_y;
	int pos;
	int color;

	pos_x = data->ray.hit_text_x;
	pct = (double)(y - ray->vert_up) / (ray->vert_down - ray->vert_up);
	pos_y = pct * data->text_e.width;
	pos = (pos_y * data->text_s.line_len + pos_x * data->text_s.bpp / 8);
	color = get_color_inv(data->text_s.addr[pos], data->text_s.addr[pos + 1], data->text_s.addr[pos + 2]);
	return(color);
}

int color_w(t_data *data, t_ray *ray, int y)
{
	int pos_x;
	double pct;
	int pos_y;
	int pos;
	int color;

	pos_x = data->ray.hit_text_x;
	pct = (double)(y - ray->vert_up) / (ray->vert_down - ray->vert_up);
	pos_y = pct * data->text_e.width;
	pos = (pos_y * data->text_w.line_len + pos_x * data->text_w.bpp / 8);
	color = get_color_inv(data->text_w.addr[pos], data->text_w.addr[pos + 1], data->text_w.addr[pos + 2]);
	return(color);
}

int color_e(t_data *data, t_ray *ray, int y)
{
	int pos_x;
	double pct;
	int pos_y;
	int pos;
	int color;

	pos_x = ray->hit_text_x;
	pct = (double)(y - ray->vert_up) / (ray->vert_down - ray->vert_up);
	pos_y = pct * data->text_e.width;
	pos = (pos_y * data->text_e.line_len + pos_x * data->text_e.bpp / 8);
	color = get_color_inv(data->text_e.addr[pos], data->text_e.addr[pos + 1], data->text_e.addr[pos + 2]);
	return(color);
}

