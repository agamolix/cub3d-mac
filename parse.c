/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_cf(char *line, t_data *data)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		line = skip_space(line + 1);
		calc_rgb(data, line);
		convert_fc(&data->color, &data->color_fc, 'f');
		printf("F = %d,%d,%d\n", data->color_fc.fr, data->color_fc.fg, data->color_fc.fb);
		data->color_fc.fok += 1;
	}
	else
	{
		line = skip_space(line + 1);
		calc_rgb(data, line);
		convert_fc(&data->color, &data->color_fc, 'c');
		printf("C = %d,%d,%d\n", data->color_fc.cr, data->color_fc.cg, data->color_fc.cb);
		data->color_fc.cok += 1;
	}
}

void parse_ns(char *line, t_data *data)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ') 
	{
		line = skip_space(line + 2);
		line = skip_end_space(line);
		data->text_n.path = line;
		printf("NO = %s\n", data->text_n.path);
		data->text_n.ok += 1;
	}
	else
	{
		line = skip_space(line + 2);
		line = skip_end_space(line);
		data->text_s.path = line;
		printf("SO = %s\n", data->text_s.path);
		data->text_s.ok += 1;
	}
}

void parse_we(char *line, t_data *data)
{
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		line = skip_space(line + 2);
		line = skip_end_space(line);
		data->text_w.path = line;
		printf("WE = %s\n", data->text_w.path);
		data->text_w.ok += 1;
	}
	else
	{
		line = skip_space(line + 2);
		line = skip_end_space(line);
		data->text_e.path = line;
		printf("EA = %s\n", data->text_e.path);
		data->text_e.ok += 1;
	}
}

void check_errors(t_data *data)
{
	if (data->text_n.ok != 1)
		exit_error(data, "ERROR: texture NO");
	if (data->text_s.ok != 1)
		exit_error(data, "ERROR: texture SO");
	if (data->text_w.ok != 1)
		exit_error(data, "ERROR: texture WE");
	if (data->text_e.ok != 1)
		exit_error(data, "ERROR: texture EA");
	if (data->color_fc.fok != 1)
		exit_error(data, "ERROR: color Floor");
	if (data->color_fc.cok != 1)
		exit_error(data, "ERROR: color Ceiling");
}

void parse(int fd, t_data *data)
{
	char *line;
	int i = 0;

	while ((line = get_next_line(fd)) != 0)
	{
		line = skip_space(line);
		if ((line[0] == 'F' && line[1] == ' ') || (line[0] == 'C' && line[1] == ' '))
			parse_cf(line, data);
		else if ((line[0] == 'N' && line[1] == 'O' && line[2] == ' ') || (line[0] == 'S' && line[1] == 'O' && line[2] == ' '))
			parse_ns(line, data);
		else if ((line[0] == 'W' && line[1] == 'E' && line[2] == ' ') || (line[0] == 'E' && line[1] == 'A' && line[2] == ' '))
			parse_we(line, data);
		else if (line[0] == '1')
		{
			data->map.start_line = i;
			break;
		}
		else if (line[0] != '\n')
			exit_error(data, "ERROR: caractère non autorisé");
		i++;
	}
	check_errors(data); 
}
