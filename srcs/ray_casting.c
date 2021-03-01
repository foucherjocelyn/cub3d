/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:58:41 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/27 19:02:08 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_casting(t_scene *scene, t_ray_var *var, int x)
{
	var->camera_x = 2 * x / (double)scene->r_width - 1;
	var->ray_dir_x = scene->player.dir_x
		+ scene->player.plane_x * var->camera_x;
	var->ray_dir_y = scene->player.dir_y
		+ scene->player.plane_y * var->camera_x;
	var->map_x = (int)scene->player.pos_x;
	var->map_y = (int)scene->player.pos_y;
	if (var->ray_dir_x == 0)
	{
		var->delta_dist_x = 1;
		var->delta_dist_y = 0;
	}
	else if (var->ray_dir_x == 0)
	{
		var->delta_dist_x = 0;
		var->delta_dist_y = 1;
	}
	else
	{
		var->delta_dist_x = fabs(1 / var->ray_dir_x);
		var->delta_dist_y = fabs(1 / var->ray_dir_y);
	}
	var->hit = 0;
}

void	ray_casting(t_scene *scene, t_ray_var *var)
{
	if (var->ray_dir_y < 0)
	{
		var->step_y = -1;
		var->side_dist_y = (scene->player.pos_y - var->map_y)
			* var->delta_dist_y;
	}
	else
	{
		var->step_y = 1;
		var->side_dist_y = (var->map_y + 1.0 - scene->player.pos_y)
			* var->delta_dist_y;
	}
	if (var->ray_dir_x < 0)
	{
		var->step_x = -1;
		var->side_dist_x = (scene->player.pos_x - var->map_x)
			* var->delta_dist_x;
	}
	else
	{
		var->step_x = 1;
		var->side_dist_x = (var->map_x + 1.0 - scene->player.pos_x)
			* var->delta_dist_x;
	}
	perform_dda(scene, var);
}

void	perform_dda(t_scene *scene, t_ray_var *var)
{
	while (var->hit == 0)
	{
		if (var->side_dist_y < var->side_dist_x)
		{
			var->side_dist_y += var->delta_dist_y;
			var->map_y += var->step_y;
			var->side = 0;
			if (var->map_y < (int)scene->player.pos_y)
				var->side = 1;
		}
		else
		{
			var->side_dist_x += var->delta_dist_x;
			var->map_x += var->step_x;
			var->side = 2;
			if (var->map_x < (int)scene->player.pos_x)
				var->side = 3;
		}
		if (scene->map[var->map_y][var->map_x] == '1')
			var->hit = 1;
	}
}
