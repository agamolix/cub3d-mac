/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/16 09:50:33 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(int r, int g, int b)
{
	int	res;

	res = 0;
	res += r;
	res = res << 8;
	res += g;
	res = res << 8;
	res += b;
	return (res);
}

int	get_color_inv(int r, int g, int b)
{
	int	res;

	res = 0;
	res += b;
	res = res << 8;
	res += g;
	res = res << 8;
	res += r;
	return (res);
}

char	*convert_rgb(t_data *data, char *rgb, char *str, char c)
{
	int	i;

	i = 0;
	while (str[0] && str[0] != c)
	{
		rgb[i] = str[0];
		i++;
		str++;
	}
	rgb[i] = 0;
	rgb = skip_space(rgb);
	rgb = skip_end_space(rgb);
	str++;
	check_rgb_error(data, rgb);
	return (str);
}

void	calc_rgb(t_data *data, char *str)
{
	check_comma(data, str);
	data->color.r = malloc((str_len(str) + 1) * sizeof(char));
	data->color.g = malloc((str_len(str) + 1) * sizeof(char));
	data->color.b = malloc((str_len(str) + 1) * sizeof(char));
	str = convert_rgb(data, data->color.r, str, ',');
	str = convert_rgb(data, data->color.g, str, ',');
	str = convert_rgb(data, data->color.b, str, '\n');
}

void	convert_fc(t_data *data, t_color *color, t_color_fc *fc, char c)
{
	if (c == 'f')
	{
		fc->fr = my_atoi(color->r);
		fc->fg = my_atoi(color->g);
		fc->fb = my_atoi(color->b);
		free(color->r);
		free(color->g);
		free(color->b);
	}
	else
	{
		fc->cr = my_atoi(color->r);
		fc->cg = my_atoi(color->g);
		fc->cb = my_atoi(color->b);
		free(color->r);
		free(color->g);
		free(color->b);
	}
}
