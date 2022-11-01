/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/01 03:47:59 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_data *data)
{
	if (!(data->mlx_ptr = mlx_init()))
		exit_error(data, "ERROR: could not start mlx");
	if (!(data->text_n.text_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_n.path, &data->text_n.width, &data->text_n.height)))
		exit_error(data, "ERROR: texture NO");
    data->text_n.addr = (unsigned char *)mlx_get_data_addr(data->text_n.text_ptr, &data->text_n.bpp, &data->text_n.line_len, &data->text_n.endian);
	if (!(data->text_s.text_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_s.path, &data->text_s.width, &data->text_s.height)))
		exit_error(data, "ERROR: texture SO");
    data->text_s.addr = (unsigned char *)mlx_get_data_addr(data->text_s.text_ptr, &data->text_s.bpp, &data->text_s.line_len, &data->text_s.endian);
	if (!(data->text_w.text_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_w.path, &data->text_w.width, &data->text_w.height)))
		exit_error(data, "ERROR: texture WE");
    data->text_w.addr = (unsigned char *)mlx_get_data_addr(data->text_w.text_ptr, &data->text_w.bpp, &data->text_w.line_len, &data->text_w.endian);
	if (!(data->text_e.text_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_e.path, &data->text_e.width, &data->text_e.height)))
		exit_error(data, "ERROR: texture EA");
    data->text_e.addr = (unsigned char *)mlx_get_data_addr(data->text_e.text_ptr, &data->text_e.bpp, &data->text_e.line_len, &data->text_e.endian);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D")))
		exit_error(data, "ERROR: could not start window");
	if (!(data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT)))
		exit_error(data, "ERROR: could not start image");
    data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.line_len, &data->img.endian);
}

int	render(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,\
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
	mlx_hook(data.win_ptr, 2, (1L<<0), &key_down, &data);
	mlx_hook(data.win_ptr, 17, 0, &exit_clean, &data);
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	mlx_loop(data.mlx_ptr);
}
