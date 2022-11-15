/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/15 09: by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture_vars(t_data *data, t_text *text, char *texture_str)
{
	char	err[19];

	ft_strlcpy(err, "Error: texture ", 16);
	ft_strncat(err, texture_str, 2);
	text->text_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
				text->path, &text->width, &text->height);
	if (!(text->text_ptr))
		exit_error(data, err);
	text->addr = (unsigned char *)mlx_get_data_addr(text->text_ptr, \
									&text->bpp, &text->line_len, &text->endian);
}

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
		exit_error(data, "ERROR: could not start mlx");
	set_texture_vars(data, &data->text_n, "NO");
	set_texture_vars(data, &data->text_s, "SO");
	set_texture_vars(data, &data->text_w, "WE");
	set_texture_vars(data, &data->text_e, "EA");
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
									WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!(data->win_ptr))
		exit_error(data, "ERROR: could not start window");
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!(data->img.img_ptr))
		exit_error(data, "ERROR: could not start image");
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, \
										&data->img.line_len, &data->img.endian);
}

int	render(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, \
									&data->img.line_len, &data->img.endian);
	check_rays(&data->img, data, &data->ray, &data->player);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
							data->img.img_ptr, 0, 0);
	return (0);
}

int	render_next_frame(t_data *data)
{
	static int	copy_mouse_pos = -1;
	int			mouse_x;	
	int			y;
	double		angle;

	mlx_mouse_get_pos(data->win_ptr, &mouse_x, &y);
	if (copy_mouse_pos == -1)
		copy_mouse_pos = mouse_x;
	if (copy_mouse_pos != mouse_x)
	{
		angle = ((float)mouse_x - (float)copy_mouse_pos) / 25;
		key_arrows_lr(124, &data->player, angle);
		copy_mouse_pos = mouse_x;
		render(data);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		exit_start("ERROR: 1 argument (file) required");
	init(&data, argv[1]);
	init_mlx(&data);
	render(&data);
	mlx_key_hook(data.win_ptr, &key_released, &data);
	mlx_hook(data.win_ptr, 2, (1L << 0), &key_down, &data);
	mlx_hook(data.win_ptr, 17, 0, &exit_clean, &data);
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	mlx_loop(data.mlx_ptr);
}
