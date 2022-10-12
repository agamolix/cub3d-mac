/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int exit_start(char *error)
{
    printf("%s\n", error);
	exit(1);
}


int exit_error(t_data *data, char *error)
{
	if (data->map.coord)
		free(data->map.coord);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
	if (data->win_ptr)
		free(data->win_ptr);
    printf("%s\n", error);
	exit(1);
}

int exit_clean(t_data *data)
{
	free(data->map.coord);
	free(data->img.img_ptr);
	free(data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
}
