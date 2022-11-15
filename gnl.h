/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/15 07:34:10 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <stdlib.h>
# include <unistd.h>

int			ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);
int			index_nl(char *s);
char		*part1(char *s, int index);
char		*part2(char *s, int index);
char		*update_temp_line(char *temp, char **line, \
								int switch_case, int fd);
void		init_free(char **line, char **buf, int switch_case);
char		*get_next_line(int fd);

#endif
