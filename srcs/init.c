/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 11:17:24 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/22 16:31:05 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_scene *scene)
{
	g_p.move_speed = 0.2;
	g_p.rot_speed = 0.1;
	g_p.z_buffer = malloc(sizeof(double) * scene->r_width);
	find_player(scene);
	find_sprite(scene);
}

void	find_dir(t_scene *scene, char player)
{
	(void)scene;
	if (player == 'N')
	{
		g_p.dir_x = -1;
		g_p.dir_y = 0;
		g_p.plane_x = 0;
		g_p.plane_y = 0.66;
	}
	else if (player == 'S')
	{
		g_p.dir_x = 1;
		g_p.dir_y = 0;
		g_p.plane_x = 0;
		g_p.plane_y = -0.66;
	}
	else if (player == 'E')
	{
		g_p.dir_x = 0;
		g_p.dir_y = 1;
		g_p.plane_x = 0.66;
		g_p.plane_y = 0;
	}
	else if (player == 'W')
	{
		g_p.dir_x = 0;
		g_p.dir_y = -1;
		g_p.plane_x = -0.66;
		g_p.plane_y = 0;
	}
}

void	find_player(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (i < scene->nb_map_lines)
	{
		j = 0;
		while (j < ft_strlen(scene->map[i]))
		{
			if (charinstr("NSEW", scene->map[i][j]))
			{
				g_p.pos_x = i + 0.5;
				g_p.pos_y = j + 0.5;
				find_dir(scene, scene->map[i][j]);
				scene->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	find_sprite(t_scene *scene)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	scene->nb_sprites = 0;
	while (i < scene->nb_map_lines)
	{
		j = 0;
		while (j < ft_strlen(scene->map[i]))
		{
			if (scene->map[i][j] == '2')
				scene->nb_sprites++;
			j++;
		}
		i++;
	}
	scene->sprites = malloc(sizeof(t_sprite) * scene->nb_sprites);
	i = 0;
	k = 0;
	while (i < scene->nb_map_lines)
	{
		j = 0;
		while (j < ft_strlen(scene->map[i]))
		{
			if (scene->map[i][j] == '2')
			{
				scene->sprites[k].x = i + 0.5;
				scene->sprites[k].y = j + 0.5;
				scene->sprites[k].texture = 4;
				k++;
			}
			j++;
		}
		i++;
	}
}
