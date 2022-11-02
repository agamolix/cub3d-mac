/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/01 05:15:29 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_cf(char *line, t_data *data, char *line_ptr)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		line = skip_space(line + 1);
		calc_rgb(data, line);
		convert_fc(&data->color, &data->color_fc, 'f');
		printf("F = %d,%d,%d\n", data->color_fc.fr, data->color_fc.fg, data->color_fc.fb);
		data->color_fc.fok = 1;
	}
	else
	{
		line = skip_space(line + 1);
		calc_rgb(data, line);
		convert_fc(&data->color, &data->color_fc, 'c');
		printf("C = %d,%d,%d\n", data->color_fc.cr, data->color_fc.cg, data->color_fc.cb);
		data->color_fc.cok = 1;
	}
	free(line_ptr);
}

void parse_ns(char *line, t_data *data, char *line_ptr)
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

void	check_errors(t_data *data)
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
	char *line_ptr;
	int i = 0;

	while ((line_ptr = get_next_line(fd)) != 0)
	{
		line = skip_space(line_ptr);
		if ((line[0] == 'F' && line[1] == ' ') || (line[0] == 'C' && line[1] == ' '))
			parse_cf(line, data, line_ptr);
		else if ((line[0] == 'N' && line[1] == 'O' && line[2] == ' ') \
			|| (line[0] == 'S' && line[1] == 'O' && line[2] == ' '))
			parse_ns(line, data, line_ptr);
		else if ((line[0] == 'W' && line[1] == 'E' && line[2] == ' ') || (line[0] == 'E' && line[1] == 'A' && line[2] == ' '))
			parse_we(line, data, line_ptr);
		else if (line[0] == '1')
		{
			data->map.start_line = i;
			free(line_ptr);
			break ;
		}
		else if (line[0] != '\n')
		{
			free(line_ptr);
			exit_error(data, "ERROR: caractère non autorisé");
		}
		else
			free(line_ptr);
		i++;
	}
	check_errors(data); 
}
