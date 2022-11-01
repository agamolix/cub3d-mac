/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/11/01 03:53:04 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include "gnl.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800
#define ROTATION_ANGLE 0.05
#define MOVE_STEP 0.1

#define PI 3.14159265358979323846

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int	bpp;
	int	line_len;
	int	endian;
}	t_img;

typedef struct s_color
{
	char *r;
	char *g;
	char *b;
}	t_color;

typedef struct s_color_fc
{
	int	fr;
	int	fg;
	int	fb;
	int	fok;
	int	color_f;
	int	cr;
	int	cg;
	int	cb;
	int	cok;
	int	color_c;
}	t_color_fc;

typedef struct s_text_n
{
	void	*text_ptr;
	unsigned char	*addr;
	char 	*path;
	char	*free_ptr;
	int	bpp;
	int	line_len;
	int	endian;
	int 	width;
	int 	height;
	int	ok;
}	t_text_n;

typedef struct s_text_s
{
	void	*text_ptr;
	unsigned char	*addr;
	char 	*path;
	char	*free_ptr;
	int	bpp;
	int	line_len;
	int	endian;
	int 	width;
	int 	height;
	int	ok;
}	t_text_s;

typedef struct s_text_w
{
	void	*text_ptr;
	unsigned char	*addr;
	char 	*path;
	char	*free_ptr;
	int	bpp;
	int	line_len;
	int	endian;
	int 	width;
	int 	height;
	int	ok;
}	t_text_w;

typedef struct s_text_e
{
	void	*text_ptr;
	unsigned char	*addr;
	char 	*path;
	char	*free_ptr;
	int	bpp;
	int	line_len;
	int	endian;
	int 	width;
	int 	height;
	int	ok;
}	t_text_e;

typedef struct s_player
{
	double			x;
	double			y;
	int			x_int;
	int			y_int;
	double			x_double;
	double			y_double;
	double			dir_x;
	double			dir_x0;
	double 		dir_y;
	double 		plane_x;
	double 		plane_x0;
	double			plane_y;
	int			temp_x;
	int			temp_y;
	int			start_pos;
}	t_player;


typedef struct s_ray
{
	double			pos_inside_cam;
	double			dir_x;
	double			dir_y;	
	double 		ec_x;
	double			ec_y;
	double 		ec_x_suiv;
	double			ec_y_suiv;
	int 			ec_x_sens;
	int 			ec_y_sens;
	int			dir_nsew;
	int			player_line;
	int			player_col;
	double 		distance;
	int			col;
	int			vert_up;
	int			vert_down;
	double 		hit_wall_x;
	int			hit_text_x;
}	t_ray;


typedef struct s_coord
{
	int			line;
	int			col;	
	int			value;
}	t_coord;

typedef struct s_map
{
	int		start_line;
	int 		nb_line;
	int			nb_col;
	t_coord		*coord;
}	t_map;

typedef struct	s_data {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_text_n	text_n;
	t_text_s	text_s;
	t_text_e	text_e;
	t_text_w	text_w;
	t_color_fc	color_fc;
	t_color	color;
	t_map	map;
	t_player player;
	t_ray	ray;
	
}	t_data;


//-----------------main-------------------
void	init_mlx(t_data *data);
int	render(t_data *data);
int	main(int argc, char **argv);

//-----------------init-------------------
void init_ray(t_data *data);
void modify_player(t_data *data);
void init_player(t_data *data);
void init_texture_fc(t_data *data);
void init(t_data *data, char *argv);

//-----------------file-------------------
void	calc_map(t_map *map, int fd);
void verify_extern(t_data *data, t_map *map);
void verify_intern(t_data *data, t_map *map);
int open_file(t_data *data, t_map *map, char *path);

//-----------------parse-------------------
void parse_cf(char *line, t_data *data);
void parse_ns(char *line, t_data *data, char *line_ptr);
void parse_we(char *line, t_data *data, char *line_ptr);
void check_errors(t_data *data);
void parse(int fd, t_data *data);

//-----------------populate-------------------
void populate_case_nswe(t_data *data, char c);
void populate_map_cases(t_data *data, char *line, int i, int j);
void	populate_map(t_data *data, t_map *map, int fd);

//-----------------distance-------------------
void calc_ec_suiv(t_ray *ray);
void calc_ec(t_ray *ray, t_player *player);
void dist_loop(int stop, t_data *data, t_ray *ray);
void calc_dist(t_data *data, t_ray *ray, t_player *player);

//-----------------rays-------------------
void calc_vertical(t_ray *ray);
void trace(t_img *img, t_data *data, t_ray *ray);
void check_rays(t_img *img, t_data *data, t_ray *ray, t_player *player);

//-----------------exit-------------------
int exit_start(char *error);
int exit_error(t_data *data, char *error);
int exit_clean(t_data *data);

//-----------------keys-------------------
void key_up_down(int key, t_data *data, t_player *player);
void key_left_right(int key, t_data *data, t_player *player);
void key_arrows_lr(int key, t_player *player, double angle);
int	key_released(int key, t_data *data);
int	key_down(int key, t_data *data);

//-----------------text_color-------------------
int color_n(t_data *data, t_ray *ray, int y);
int color_s(t_data *data, t_ray *ray, int y);
int color_w(t_data *data, t_ray *ray, int y);
int color_e(t_data *data, t_ray *ray, int y);

//-----------------color-------------------
int get_color(int r, int g, int b);
int get_color_inv(int r, int g, int b);
char *convert_rgb(char *rgb, char *str, char c);
void calc_rgb(t_data *data, char *str);
void convert_fc(t_color *color, t_color_fc *fc, char c);

//-----------------atoi-------------------
char    *remove_space(char *str);
int convert(char *str, int len_nb, int sign);
int	calc_len_nb(char *str);
int my_atoi(const char *nptr);

//-----------------utils_file-------------------
char *skip_space(char *str);
char *skip_end_space(char *str);
void check_comma(t_data *data, char *str);

//-----------------utils_global-------------------
void	put_pix_on_img(t_img *img, int x, int y, int color);
int str_len(char *str);
int val_map(t_map *map, int i, int j);
int dval_map(t_data *data, int i, int j);


#endif
