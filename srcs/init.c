/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 11:17:24 by jfoucher          #+#    #+#             */
/*   Updated: 2020/12/05 12:34:03 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init()
{
	g_s.r_width = 1280;
	g_s.r_height = 1024;
	g_s.north = "pics/bluestone.xpm";
	g_s.south = "pics/eagle.xpm";
	g_s.west = "pics/redbrick.xpm";
	g_s.east = "pics/greystone.xpm";
	g_s.sprite = "pics/barrel.xpm";
	g_s.floor = 0xBBBBBB;
	g_s.ceiling = 0x0000FF;
	g_s.m_width = 24;
	g_s.m_height = 24;
	g_p.pos_x = 22.0;
	g_p.pos_y = 11.5;
	g_p.dir_x = -1;
	g_p.dir_y = 0;
	g_p.plane_x = 0;
	g_p.plane_y = 0.66;
	g_p.move_speed = 0.2;
	g_p.rot_speed = 0.1;
	g_p.z_buffer = malloc(sizeof(double) * g_s.r_width);
}
