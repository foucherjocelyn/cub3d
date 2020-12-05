/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:16:48 by jfoucher          #+#    #+#             */
/*   Updated: 2020/12/05 11:44:54 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define NUM_SPRITES 19
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 1024

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

int				render(t_data *texture);

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
	int				m_width;
	int				m_height;
	char			**map;
}				t_scene;

extern t_scene g_s;

extern int				g_world_map[MAP_WIDTH][MAP_HEIGHT];

typedef struct	s_sprite
{
	double	x;
	double	y;
	int		texture;
}				t_sprite;

void    load_image(t_data *img, char *path);
int		key_press(int keycode);
void	init();

#endif
