/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:16:48 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/19 15:14:36 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "get_next_line/get_next_line.h"

# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}				t_data;

typedef struct	s_sprite
{
	double	x;
	double	y;
	double	distance;
}				t_sprite;

typedef struct	s_ray_var {
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
	int		line_height;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		draw_start;
	int		draw_end;
}				t_ray_var;

typedef	struct	s_sprite_var
{
	int		sprite_height;
	int		sprite_width;
	int		sprite_screen_x;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	double	transform_x;
	double	transform_y;
	int		tex_x;
	int		tex_y;
	int		stripe;
	int		y;
}				t_sprite_var;

typedef struct	s_player {
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	move_speed;
	double	rot_speed;
	double	plane_x;
	double	plane_y;
	double	*z_buffer;
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
	unsigned int	t_color;
	int				floor;
	int				ceiling;
	int				nb_sprites;
	t_sprite		*sprites;
	char			**map;
	t_data			*texture;
	int				nb_map_lines;
}				t_scene;

typedef struct	s_elem {
	char	*identifier;
	int		parsed;
}				t_elem;

int				render(t_scene *scene, int save);
void			load_image(t_scene *scene, t_data *img, char *path);
int				key_press(int keycode, t_scene *scene);
void			init(t_scene *scene);
void			find_sprite(t_scene *scene);
char			*ft_strcpy(char *dest, char *src);
void			parsing(char *file, t_scene *scene);
void			p_texture(t_scene *scene, char *line, char **texture);
void			parsing2(char *line, t_scene *scene);
void			p_res(char *line, t_scene *scene);
void			p_color(t_scene *scene, char *line, int *color);
int				res_atoi(t_scene *scene, char *line);
int				color_atoi(t_scene *scene, char *line, int *i);
void			count_map_lines(t_scene *scene, char *line);
int				charinstr(char *str, char c);
void			parse_map(char *file, t_scene *scene);
void			find_player(t_scene *scene);
void			find_dir(t_scene *scene, char player);
void			sort_sprites(t_scene *scene);
void			ray_casting(t_scene *scene, t_ray_var *var);
void			perform_dda(t_scene *scene, t_ray_var *var);
void			draw_line(t_scene *scene, t_ray_var *var, t_data *img, int x);
void			sprite_casting(t_scene *scene, t_data *img);
void			count_sprite(t_scene *scene);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			rotate_left(t_player *p);
void			rotate_left(t_player *p);
void			move_forward_backward(t_scene *scene, t_player *p, char dir);
void			move_sideways(t_scene *scene, t_player *p, char dir);
void			init_ray_casting(t_scene *scene, t_ray_var *var, int x);
void			init_draw_line(t_scene *scene, t_ray_var *var);
void			init_draw_line2(t_scene *scene, t_ray_var *var);
void			draw_sprite(t_scene *scene, t_data *img, t_sprite_var *var);
void			draw_sprite2(t_scene *scene, t_data *img, t_sprite_var *var);
void			init_sprite_casting(t_scene *scene, t_sprite_var *var, int i);
void			error(t_scene *scene, char *msg);
void			init_parsing(t_scene *scene);
void			check_map(t_scene *scene);
void			is_map_closed(t_scene *scene);
void			are_space_around(t_scene *scene, int i, int j);
void			count_players(t_scene *scene);
int				ft_strcmp(char *s1, char *s2);
void			save_bmp(t_scene *scene, t_data *img);
void			bmp_header(t_scene *scene, t_data *img, int fd);
int				ft_str_at_end(char *str, char *end);
void			call_load(t_scene *scene);
int				ft_exit(t_scene *scene);
void			null_vars(t_scene *scene);
void			free_map(t_scene *scene);
void			free_texture(t_scene *scene);
int				ft_atoi(t_scene *scene, char *line, int *i);
void			free_and_error(t_scene *scene, char *msg, char *line);

#endif
