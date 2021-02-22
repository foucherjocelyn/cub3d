/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:16:48 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/22 16:12:55 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "get_next_line/get_next_line.h"

# define NUM_SPRITES 8
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			w;
	int			h;
}				t_data;

typedef struct	s_ptr {
	void *mlx;
	void *win;
}				t_ptr;

typedef struct	s_sprite
{
	double	x;
	double	y;
	int		texture;
}				t_sprite;

t_ptr g_ptr;

typedef struct	s_player {
	double			dir_x;
	double			dir_y;
	double			pos_x;
	double			pos_y;
	double			move_speed;
	double			rot_speed;
	double			plane_x;
	double			plane_y;
	double			*z_buffer;
}				t_player;

extern t_player g_p;

typedef struct	s_scene {
	int				r_width;
	int				r_height;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
	int				floor;
	int				ceiling;
	int				nb_sprites;
	t_sprite		*sprites;
	char			**map;
	t_data			*texture;
	int				nb_map_lines;
}				t_scene;

typedef struct	s_elem {
	char			*identifier;
	int				parsed;
}				t_elem;

int		render(t_scene *scene);
void    load_image(t_data *img, char *path);
int		key_press(int keycode, t_scene *scene);
void	init(t_scene *scene);
void    find_sprite(t_scene *scene);
char	*ft_strcpy(char *dest, char *src);
void	parsing(char *file, t_scene *scene);
void	p_texture(char *line, char **texture);
void	parsing2(char *line, t_scene *scene);
void	p_res(char *line, t_scene *scene);
void	p_color(char *line, int *color);
int		res_atoi(char *line);
int		color_atoi(char *line, int *i);
void	count_map_lines(t_scene *scene, char *line);
int		charinstr(char *str, char c);
void	parse_map(char *file, t_scene *scene);
void	find_player(t_scene *scene);
void	find_dir(t_scene *scene, char player);

#endif
