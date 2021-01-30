/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 11:17:24 by jfoucher          #+#    #+#             */
/*   Updated: 2021/01/30 15:44:43 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_scene *scene)
{
	scene->r_width = 1280;
	scene->r_height = 1024;
	scene->north = "pics/redbrick.xpm";
	scene->south = "pics/eagle.xpm";
	scene->west = "pics/bluestone.xpm";
	scene->east = "pics/greystone.xpm";
	scene->sprite = "pics/barrel.xpm";
	scene->floor = 0xBBBBBB;
	scene->ceiling = 0x0000FF;
	scene->m_width = 24;
	scene->m_height = 24;
	g_p.pos_x = 22.0;
	g_p.pos_y = 11.5;
	g_p.dir_x = -1;
	g_p.dir_y = 0;
	g_p.plane_x = 0;
	g_p.plane_y = 0.66;
	g_p.move_speed = 0.2;
	g_p.rot_speed = 0.1;
	g_p.z_buffer = malloc(sizeof(double) * scene->r_width);
	find_sprite(scene);
}

void	find_sprite(t_scene *scene)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	scene->nb_sprites = 0;
	while (i < scene->m_width)
	{
		j = 0;
		while (j < scene->m_height)
		{
			if (g_world_map[i][j] == 2)
				scene->nb_sprites++;
			j++;
		}
		i++;
	}
	scene->sprites = malloc(sizeof(t_sprite) * scene->nb_sprites);
	i = 0;
	k = 0;
	while (i < scene->m_width)
	{
		j = 0;
		while (j < scene->m_height)
		{
			if (g_world_map[i][j] == 2)
			{
				scene->sprites[k].x = i + 0.5;
				scene->sprites[k].y = j + 0.5;
				scene->sprites[k].texture = g_world_map[i][j] + 2;
				k++;
			}
			j++;
		}
		i++;
	}
}
