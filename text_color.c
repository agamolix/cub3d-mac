/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/15 10:32:57 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_text_color(t_data *data, t_text *text, t_ray *ray, int y)
{
	int		pos_x;
	double	pct;
	int		pos_y;
	int		pos;
	int		color;

	pos_x = data->ray.hit_text_x;
	pct = (double)(y - ray->vert_up) / (ray->vert_down - ray->vert_up);
	pos_y = pct * data->text_e.width;
	pos = (pos_y * text->line_len + pos_x * text->bpp / 8);
	color = get_color_inv(text->addr[pos], text->addr[pos + 1], \
							text->addr[pos + 2]);
	return (color);
}
