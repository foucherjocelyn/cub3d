/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:50:11 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/11 10:35:07 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_scene *scene)
{
	int			i;
	t_sprite	tmp;

	i = 0;
	while (i < scene->nb_sprites)
	{
		scene->sprites[i].distance = (
				(scene->player.pos_x - scene->sprites[i].x) *
				(scene->player.pos_x - scene->sprites[i].x) +
				(scene->player.pos_y - scene->sprites[i].y) *
				(scene->player.pos_y - scene->sprites[i].y));
		i++;
	}
	i = 0;
	while (i < scene->nb_sprites - 1)
	{
		if (scene->sprites[i].distance < scene->sprites[i + 1].distance)
		{
			tmp = scene->sprites[i];
			scene->sprites[i] = scene->sprites[i + 1];
			scene->sprites[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

void	draw_sprite(t_scene *scene, t_data *img, t_sprite_var *var)
{
	var->stripe = var->draw_start_x;
	while (var->stripe < var->draw_end_x)
	{
		var->tex_x = (int)(256 * (var->stripe -
					(-var->sprite_width / 2 + var->sprite_screen_x))
				* scene->texture[4].h / var->sprite_width) / 256;
		if (var->transform_y > 0 && var->stripe > 0 && var->stripe <
				scene->r_width && var->transform_y <
				scene->player.z_buffer[var->stripe])
		{
			var->y = var->draw_start_y;
			while (var->y < var->draw_end_y)
			{
				draw_sprite2(scene, img, var);
				var->y++;
			}
		}
		var->stripe++;
	}
}

void	draw_sprite2(t_scene *scene, t_data *img, t_sprite_var *var)
{
	int				d;
	unsigned int	color;

	d = (var->y) * 256 - scene->r_height * 128 + var->sprite_height * 128;
	var->tex_y = ((d * scene->texture[4].h) / var->sprite_height) / 256;
	color = *(unsigned int*)(scene->texture[4].addr
			+ (var->tex_y * scene->texture[4].line_length + var->tex_x
				* (scene->texture[4].bits_per_pixel / 8)));
	if ((color != scene->t_color))
		my_mlx_pixel_put(img, var->stripe, var->y, color);
}

void	init_sprite_casting(t_scene *scene, t_sprite_var *var, int i)
{
	double			sprite_x;
	double			sprite_y;
	double			inv_det;

	sprite_x = scene->sprites[i].x -
		scene->player.pos_x;
	sprite_y = scene->sprites[i].y -
		scene->player.pos_y;
	inv_det = 1.0 / (scene->player.plane_y * scene->player.dir_x -
			scene->player.dir_y * scene->player.plane_x);
	var->transform_x = inv_det * (scene->player.dir_x * sprite_y -
			scene->player.dir_y * sprite_x);
	var->transform_y = inv_det * (-scene->player.plane_x * sprite_y +
			scene->player.plane_y * sprite_x);
	var->sprite_screen_x = (int)((scene->r_width / 2) *
			(1 + var->transform_x / var->transform_y));
}

void	sprite_casting(t_scene *scene, t_data *img)
{
	t_sprite_var	var;
	int				i;

	sort_sprites(scene);
	i = 0;
	while (i < scene->nb_sprites)
	{
		init_sprite_casting(scene, &var, i);
		var.sprite_height = abs((int)(scene->r_height / (var.transform_y)));
		var.draw_start_y = -var.sprite_height / 2 + scene->r_height / 2;
		if (var.draw_start_y < 0)
			var.draw_start_y = 0;
		var.draw_end_y = var.sprite_height / 2 + scene->r_height / 2;
		if (var.draw_end_y >= scene->r_height)
			var.draw_end_y = scene->r_height - 1;
		var.sprite_width = abs((int)(((scene->r_width) / (var.transform_y))/ 1.32));
		var.draw_start_x = -var.sprite_width / 2 + var.sprite_screen_x;
		if (var.draw_start_x < 0)
			var.draw_start_x = 0;
		var.draw_end_x = var.sprite_width / 2 + var.sprite_screen_x;
		if (var.draw_end_x >= scene->r_width)
			var.draw_end_x = scene->r_width - 1;
		draw_sprite(scene, img, &var);
		i++;
	}
}
