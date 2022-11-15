/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:51:55 by gmillon           #+#    #+#             */
/*   Updated: 2022/11/15 09:54:57 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_cf(char *line, t_data *data, char *line_ptr)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		line = skip_space(line + 1);
		calc_rgb(data, line);
		convert_fc(&data->color, &data->color_fc, 'f');
		printf("F = %d,%d,%d\n", data->color_fc.fr, \
				data->color_fc.fg, data->color_fc.fb);
		data->color_fc.fok = 1;
	}
	else
	{
		line = skip_space(line + 1);
		calc_rgb(data, line);
		convert_fc(&data->color, &data->color_fc, 'c');
		printf("C = %d,%d,%d\n", data->color_fc.cr, \
				data->color_fc.cg, data->color_fc.cb);
		data->color_fc.cok = 1;
	}
	free(line_ptr);
}

void	parse_ns(char *line, t_data *data, char *line_ptr)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		line = skip_space(line + 2);
		line = skip_end_space(line);
		data->text_n.path = ft_strdup(line);
		free(line_ptr);
		printf("NO = %s\n", data->text_n.path);
		data->text_n.ok = 1;
	}
	else
	{
		line = skip_space(line + 2);
		line = skip_end_space(line);
		data->text_s.path = ft_strdup(line);
		free(line_ptr);
		printf("SO = %s\n", data->text_s.path);
		data->text_s.ok = 1;
	}
}

void	parse_we(char *line, t_data *data, char *line_ptr)
{
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		line = skip_space(line + 2);
		line = skip_end_space(line);
		data->text_w.path = ft_strdup(line);
		free(line_ptr);
		printf("WE = %s\n", data->text_w.path);
		data->text_w.ok += 1;
	}
	else
	{
		line = skip_space(line + 2);
		line = skip_end_space(line);
		data->text_e.path = ft_strdup(line);
		free(line_ptr);
		printf("EA = %s\n", data->text_e.path);
		data->text_e.ok += 1;
	}
}

int	parse_wall_texts(char *line, t_data *data, char *line_ptr)
{
	int	i;

	i = 0;
	if ((line[0] == 'F' && line[1] == ' ') || \
		(line[0] == 'C' && line[1] == ' '))
	{
		i++;
		parse_cf(line, data, line_ptr);
	}
	else if ((line[0] == 'N' && line[1] == 'O' && line[2] == ' ') \
		|| (line[0] == 'S' && line[1] == 'O' && line[2] == ' '))
	{
		i++;
		parse_ns(line, data, line_ptr);
	}
	else if ((line[0] == 'W' && line[1] == 'E' && line[2] == ' ') \
			|| (line[0] == 'E' && line[1] == 'A' && line[2] == ' '))
	{
		parse_we(line, data, line_ptr);
		i++;
	}
	return (i);
}
