/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:42:43 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/11 10:34:25 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_draw_line(t_scene *scene, t_ray_var *var)
{
	if (var->side < 2)
		var->perp_wall_dist = (var->map_y - scene->player.pos_y
				+ (1 - var->step_y) / 2) / var->ray_dir_y;
	else
		var->perp_wall_dist = (var->map_x - scene->player.pos_x
				+ (1 - var->step_x) / 2) / var->ray_dir_x;
	var->line_height = (int)(scene->r_height / var->perp_wall_dist);
	if (var->perp_wall_dist < 0.000001)
		var->line_height = 2147483647;
	var->draw_start = -var->line_height / 2 + scene->r_height / 2;
	if (var->draw_start < 0)
		var->draw_start = 0;
	var->draw_end = var->line_height / 2 + scene->r_height / 2;
	if (var->draw_end >= scene->r_height)
		var->draw_end = scene->r_height - 1;
}

void	init_draw_line2(t_scene *scene, t_ray_var *var)
{
	if (var->side < 2)
		var->wall_x = scene->player.pos_x
			+ var->perp_wall_dist * var->ray_dir_x;
	else
		var->wall_x = scene->player.pos_y
			+ var->perp_wall_dist * var->ray_dir_y;
	var->wall_x -= floor((var->wall_x));
	var->tex_x = (int)(var->wall_x * (double)scene->texture[var->side].w);
	if (var->side < 2 && var->ray_dir_y > 0)
		var->tex_x = scene->texture[var->side].w - var->tex_x - 1;
	if (var->side >= 2 && var->ray_dir_x < 0)
		var->tex_x = scene->texture[var->side].w - var->tex_x - 1;
	var->step = 1.0 * scene->texture[var->side].h / var->line_height;
	var->tex_pos = (var->draw_start - scene->r_height
			/ 2 + var->line_height / 2) * var->step;
}

void	draw_line(t_scene *scene, t_ray_var *var, t_data *img, int x)
{
	int				y;
	unsigned int	color;

	init_draw_line(scene, var);
	init_draw_line2(scene, var);
	y = var->draw_start;
	while (y < var->draw_end)
	{
		var->tex_y = (int)var->tex_pos;
		var->tex_pos += var->step;
		color = *(unsigned int*)(scene->texture[var->side].addr +
				(var->tex_y * scene->texture[var->side].line_length + var->tex_x
				* (scene->texture[var->side].bits_per_pixel / 8)));
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
	y = 0;
	while (y < var->draw_start)
		my_mlx_pixel_put(img, x, y++, scene->ceiling);
	y = var->draw_end;
	while (y < scene->r_height)
		my_mlx_pixel_put(img, x, y++, scene->floor);
	scene->player.z_buffer[x] = var->perp_wall_dist;
}
