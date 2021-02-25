/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:58:41 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/25 18:59:46 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting(t_scene *scene, t_ray_var *var, int x)
{
	var->camera_x = 2 * x / (double)scene->r_width - 1;
	var->ray_dir_x = scene->player.dir_x + scene->player.plane_x * var->camera_x;
	var->ray_dir_y = scene->player.dir_y + scene->player.plane_y * var->camera_x;
	var->map_x = (int)scene->player.pos_x;
	var->map_y = (int)scene->player.pos_y;

	var->delta_dist_x = (var->ray_dir_y == 0) ? 0 : ((var->ray_dir_x == 0) ? 1 : fabs(1 / var->ray_dir_x));
	var->delta_dist_y = (var->ray_dir_x == 0) ? 0 : ((var->ray_dir_y == 0) ? 1 : fabs(1 / var->ray_dir_y));

	var->hit = 0;
	if (var->ray_dir_y < 0)
	{
		var->step_y = -1;
		var->side_dist_y = (scene->player.pos_y - var->map_y) * var->delta_dist_y;
	}
	else
	{
		var->step_y = 1;
		var->side_dist_y = (var->map_y + 1.0 - scene->player.pos_y) * var->delta_dist_y;
	}
	if (var->ray_dir_x < 0)
	{
		var->step_x = -1;
		var->side_dist_x = (scene->player.pos_x - var->map_x) * var->delta_dist_x;
	}
	else
	{
		var->step_x = 1;
		var->side_dist_x = (var->map_x + 1.0 - scene->player.pos_x) * var->delta_dist_x;
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
		if (scene->map[var->map_y][var->map_x] == '1') var->hit = 1;
	}
}

void	draw_wall(t_scene *scene, t_ray_var *var, t_data *img, int x)
{
	if (var->side < 2) var->perp_wall_dist = (var->map_y - scene->player.pos_y + (1 - var->step_y) / 2) / var->ray_dir_y;
	else           var->perp_wall_dist = (var->map_x - scene->player.pos_x + (1 - var->step_x) / 2) / var->ray_dir_x;
	int lineHeight = (int)(scene->r_height / var->perp_wall_dist);
	if (var->perp_wall_dist < 0.000001)
		lineHeight = 2147483647;
	int drawStart = -lineHeight / 2 + scene->r_height / 2;
	if(drawStart < 0)drawStart = 0;
	int drawEnd = lineHeight / 2 + scene->r_height / 2;
	if(drawEnd >= scene->r_height)drawEnd = scene->r_height - 1;
	double wallX;
	if (var->side < 2) wallX = scene->player.pos_x + var->perp_wall_dist * var->ray_dir_x;
	else           wallX = scene->player.pos_y + var->perp_wall_dist * var->ray_dir_y;
	wallX -= floor((wallX));
	int texX = (int)(wallX * (double)TEX_WIDTH);
	if(var->side < 2 && var->ray_dir_y > 0) texX = TEX_WIDTH - texX - 1;
	if(var->side >= 2 && var->ray_dir_x < 0) texX = TEX_WIDTH - texX - 1;
	double step = 1.0 * TEX_HEIGHT / lineHeight;
	double texPos = (drawStart - scene->r_height / 2 + lineHeight / 2) * step;
	for(int y = drawStart; y<drawEnd; y++)
	{
		int texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		unsigned int color = *(unsigned int*)(scene->texture[var->side].addr + (texY * scene->texture[var->side].line_length + texX * (scene->texture[var->side].bits_per_pixel / 8)));
		my_mlx_pixel_put(img, x, y, color);
	}
	for(int y = 0; y<drawStart; y++)
		my_mlx_pixel_put(img, x, y, scene->ceiling);
	for(int y = drawEnd; y<scene->r_height; y++)
		my_mlx_pixel_put(img, x, y, scene->floor);
	scene->player.z_buffer[x] = var->perp_wall_dist; 
}
