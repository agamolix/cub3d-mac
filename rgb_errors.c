/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:49:46 by gmillon           #+#    #+#             */
/*   Updated: 2022/11/16 10:07:40 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_fc_err(t_color_fc *fc, t_data *data)
{
	int	err;

	err = 0;
	if (fc->fr < 0 || fc->fr > 255)
		err++;
	if (fc->fg < 0 || fc->fg > 255)
		err++;
	if (fc->fb < 0 || fc->fb > 255)
		err++;
	if (fc->cr < 0 || fc->cr > 255)
		err++;
	if (fc->cg < 0 || fc->cg > 255)
		err++;
	if (fc->cb < 0 || fc->cb > 255)
		err++;
	if (err)
		exit_error(data, "Invalid color info (not in interval 0-255)");
}

int	ft_rgb_is_num(char *str)
{
	while (*str && (ft_isdigit(*str)))
		str++;
	if (*str)
		return (0);
	return (1);
}

void	check_rgb_error(t_data *data, char *str)
{
	if ((!ft_rgb_is_num(str) || \
			!ft_rgb_is_num(str) || \
			!ft_rgb_is_num(str)))
	{
		free(data->color.r);
		free(data->color.g);
		free(data->color.b);
		exit_error(data, "Color input invalid");
	}
}
