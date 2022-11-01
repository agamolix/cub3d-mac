/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/01 03:00:18 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void key_up_down(int key, t_data *data, t_player *player)
{
	if (key == 13)
	{
		player->temp_x = (int) (player->x_double + player->dir_x * MOVE_STEP);
		player->temp_y = (int) (player->y_double + player->dir_y * MOVE_STEP);
		if(dval_map(data, player->temp_x, player->temp_y) == 0)
		{
			player->x_double += player->dir_x * MOVE_STEP;
			player->y_double += player->dir_y * MOVE_STEP;
		}
	}
	else
	{
		player->temp_x = (int) (player->x_double - player->dir_x * MOVE_STEP);
		player->temp_y = (int) (player->y_double - player->dir_y * MOVE_STEP);	
		if(dval_map(data, player->temp_x, player->temp_y) == 0)
		{
			player->x_double -= player->dir_x * MOVE_STEP;
			player->y_double -= player->dir_y * MOVE_STEP;
		}
	}
}

void key_left_right(int key, t_data *data, t_player *player)
{
	if (key == 1)
	{
		player->temp_x = (int) (player->x_double - player->dir_y * MOVE_STEP);
		player->temp_y = (int) (player->y_double + player->dir_x * MOVE_STEP);	
		if(dval_map(data, player->temp_x, player->temp_y) == 0)
		{
			player->x_double -= player->dir_y * MOVE_STEP;
			player->y_double += player->dir_x * MOVE_STEP;
		}
	}
	else
	{
		player->temp_x = (int) (player->x_double + player->dir_y * MOVE_STEP);
		player->temp_y = (int) (player->y_double - player->dir_x * MOVE_STEP);	
		if(dval_map(data, player->temp_x, player->temp_y) == 0)
		{
			player->x_double += player->dir_y * MOVE_STEP;
			player->y_double -= player->dir_x * MOVE_STEP;
		}
	}
}

void key_arrows_lr(int key, t_player *player, double angle)
{
	if (!angle)
		angle = ROTATION_ANGLE;
	if (key == 123) 
	{
		double player_dir_x0 = player->dir_x;
		player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
		player->dir_y = player_dir_x0 * sin(angle) + player->dir_y * cos(angle);
		double player_plane_x0 = player->plane_x;
		player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
		player->plane_y = player_plane_x0 * sin(angle) + player->plane_y * cos(angle);
	}
	if (key == 124) //arrow right 
	{
		double player_dir_x0 = player->dir_x;
		player->dir_x = player->dir_x * cos(-angle) - player->dir_y * sin(-angle);
		player->dir_y = player_dir_x0 * sin(-angle) + player->dir_y * cos(-angle);
		double player_plane_x0 = player->plane_x;
		player->plane_x = player->plane_x * cos(-angle) - player->plane_y * sin(-angle);
		player->plane_y = player_plane_x0 * sin(-angle) + player->plane_y * cos(-angle);
	}
}

int	key_released(int key, t_data *data)
{
	t_player *player = &data->player;

	printf("key: %d\n", key);
	if (key == 53)
		exit_clean(data);
	if (key == 13 || key == 0) 
		key_up_down(key, data, player);
	if (key == 1 || key == 2)
		key_left_right(key, data, player);
	if (key == 123 || key == 124)
		key_arrows_lr(key, player, 0);
	player->x_int = (int)player->x_double;
	player->y_int = (int)player->y_double;
	render(data);
	return(0);
}

int	key_down(int key, t_data *data)
{
	t_player *player = &data->player;

	if (key == 13 || key == 0) 
		key_up_down(key, data, player);
	if (key == 1 || key == 2)
		key_left_right(key, data, player);
	if (key == 123 || key == 124)
		key_arrows_lr(key, player, 0);
	player->x_int = (int)player->x_double;
	player->y_int = (int)player->y_double;
	render(data);
	return(0);
}
