/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:02:22 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/25 22:24:17 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_player *p)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_y;
	p->dir_y = p->dir_y * cos(-p->rot_speed)
		- p->dir_x * sin(-p->rot_speed);
	p->dir_x = old_dir_x * sin(-p->rot_speed)
		+ p->dir_x * cos(-p->rot_speed);
	old_plane_x = p->plane_y;
	p->plane_y = p->plane_y
		* cos(-p->rot_speed) - p->plane_x
		* sin(-p->rot_speed);
	p->plane_x = old_plane_x * sin(-p->rot_speed)
		+ p->plane_x * cos(-p->rot_speed);
}

void	rotate_left(t_player *p)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_y;
	p->dir_y = p->dir_y * cos(p->rot_speed)
		- p->dir_x * sin(p->rot_speed);
	p->dir_x = old_dir_x * sin(p->rot_speed)
		+ p->dir_x * cos(p->rot_speed);
	old_plane_x = p->plane_y;
	p->plane_y = p->plane_y * cos(p->rot_speed)
		- p->plane_x * sin(p->rot_speed);
	p->plane_x = old_plane_x * sin(p->rot_speed)
		+ p->plane_x * cos(p->rot_speed);
}

void	move_forward_backward(t_scene *scene, t_player *p, char dir)
{
	if (dir == 'F')
	{
		if (scene->map[(int)(p->pos_y + p->dir_y * p->move_speed)]
				[(int)p->pos_x] != '1')
			p->pos_y += p->dir_y * p->move_speed;
		if (scene->map[(int)p->pos_y]
				[(int)(p->pos_x + p->dir_x * p->move_speed)] != '1')
			p->pos_x += p->dir_x * p->move_speed;
	}
	if (dir == 'B')
	{
		if (scene->map[(int)(p->pos_y - p->dir_y * p->move_speed)]
				[(int)p->pos_x] != '1')
			p->pos_y -= p->dir_y * p->move_speed;
		if (scene->map[(int)p->pos_y]
				[(int)(p->pos_x - p->dir_x * p->move_speed)] != '1')
			p->pos_x -= p->dir_x * p->move_speed;
	}
}

void	move_sideways(t_scene *scene, t_player *p, char dir)
{
	if (dir == 'L')
	{
		if (scene->map[(int)(p->pos_y - p->plane_y * p->move_speed)]
				[(int)p->pos_x] != '1')
			p->pos_y -= p->plane_y * p->move_speed;
		if (scene->map[(int)p->pos_y]
				[(int)(p->pos_x - p->plane_x * p->move_speed)] != '1')
			p->pos_x -= p->plane_x * p->move_speed;
	}
	if (dir == 'R')
	{
		if (scene->map[(int)(p->pos_y + p->plane_y * p->move_speed)]
				[(int)p->pos_x] != '1')
			p->pos_y += p->plane_y * p->move_speed;
		if (scene->map[(int)p->pos_y]
				[(int)(p->pos_x + p->plane_x * p->move_speed)] != '1')
			p->pos_x += p->plane_x * p->move_speed;
	}
}

int		key_press(int keycode, t_scene *scene)
{
	if (keycode == KEY_W)
		move_forward_backward(scene, &(scene->player), 'F');
	if (keycode == KEY_S)
		move_forward_backward(scene, &(scene->player), 'B');
	if (keycode == KEY_A)
		move_sideways(scene, &(scene->player), 'L');
	if (keycode == KEY_D)
		move_sideways(scene, &(scene->player), 'R');
	if (keycode == KEY_RIGHT)
		rotate_right(&(scene->player));
	if (keycode == KEY_LEFT)
		rotate_left(&(scene->player));
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}
