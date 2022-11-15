/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/15 09:52:54 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	check_if_map(char *line, t_data *data, char *line_ptr, int i)
{
	if (line[0] == '1')
	{
		data->map.start_line = i;
		free(line_ptr);
		return (1);
	}
	return (0);
}

void	parse(int fd, t_data *data)
{
	char	*line;
	char	*line_ptr;
	int		i;

	i = 0;
	line_ptr = get_next_line(fd);
	while (line_ptr)
	{
		line = skip_space(line_ptr);
		if (parse_wall_texts(line, data, line_ptr))
		{
		}
		else if (check_if_map(line, data, line_ptr, i))
			break ;
		else if (line[0] != '\n')
		{
			free(line_ptr);
			exit_error(data, "ERROR: caractère non autorisé");
		}
		else
			free(line_ptr);
		i++;
		line_ptr = get_next_line(fd);
	}
	check_errors(data);
}
