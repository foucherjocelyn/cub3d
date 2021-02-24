/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:16:48 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/23 22:32:58 by jfoucher         ###   ########.fr       */
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

typedef struct	s_sprite
{
	double	x;
	double	y;
	int		texture;
}				t_sprite;

typedef struct	s_var_raycasting {
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}				t_var_raycasting;

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

typedef struct	s_scene {
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		player;
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
	int				*sprite_order;
	double			*sprite_distance;
	char			**map;
	t_data			*texture;
	int				nb_map_lines;
}				t_scene;

typedef struct	s_elem {
	char			*identifier;
	int				parsed;
}				t_elem;

int		render(t_scene *scene);
void	load_image(t_scene *scene, t_data *img, char *path);
int		key_press(int keycode, t_scene *scene);
void	init(t_scene *scene);
void	find_sprite(t_scene *scene);
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
void	sortSprites(int *order, double *dist, int amount);

#endif
