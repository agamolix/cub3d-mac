/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/15 10:33:28 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_space(char *str)
{
	while (str[0] && str[0] == ' ')
	{
		str++;
	}
	return (str);
}

char	*skip_end_space(char *str)
{
	int	i;

	i = str_len(str);
	i -= 1;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\n'))
		i--;
	str[i + 1] = 0;
	return (str);
}

void	check_comma(t_data *data, char *str)
{
	int	count;
	int	len;

	count = 0;
	len = 0;
	while (str[len])
	{
		if (str[len] == ',')
			count += 1;
		len++;
	}
	if (count != 2)
		exit_error(data, "ERROR: floor color");
}
