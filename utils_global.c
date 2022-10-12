/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pix_on_img(t_img *img, int x, int y, int color)
{
	char    *pix;

    if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		pix = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pix = color;
	}
}

int str_len(char *str)
{
    int len;

    len = 0;
    while (str[len])
        len++;
    return len;
}

int val_map(t_map *map, int i, int j)
{
	return (map->coord[i * map->nb_col + j].value);
}

int dval_map(t_data *data, int i, int j)
{
	return (data->map.coord[i * data->map.nb_col + j].value);
}

