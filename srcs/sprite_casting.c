/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:50:11 by jfoucher          #+#    #+#             */
/*   Updated: 2021/02/25 18:56:20 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void sort_sprites(int* order, double* dist, int amount)
{
	int	i;
	int tmp;

	i = 0;
	while (i < amount - 1)
	{
		if (dist[i] < dist[i + 1])
		{
			tmp = dist[i];
			dist[i] = dist[i + 1];
			dist[i + 1] = tmp;
			tmp = order[i];
			order[i] = order[i + 1];
			order[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

void	sprite_casting(t_scene *scene, t_data *img)
{
	for(int i = 0; i < scene->nb_sprites; i++)
	{
		scene->sprite_order[i] = i;
		scene->sprite_distance[i] = ((scene->player.pos_y - scene->sprites[i].x) * (scene->player.pos_y - scene->sprites[i].x) + (scene->player.pos_x - scene->sprites[i].y) * (scene->player.pos_x - scene->sprites[i].y)); 
	}
	sort_sprites(scene->sprite_order, scene->sprite_distance, scene->nb_sprites);

	for(int i = 0; i < scene->nb_sprites; i++)
	{
		double spriteX = scene->sprites[scene->sprite_order[i]].x - scene->player.pos_y;
		double spriteY = scene->sprites[scene->sprite_order[i]].y - scene->player.pos_x;


		double invDet = 1.0 / (scene->player.plane_y * scene->player.dir_x - scene->player.dir_y * scene->player.plane_x); 

		double transformX = invDet * (scene->player.dir_x * spriteX - scene->player.dir_y * spriteY);
		double transformY = invDet * (-scene->player.plane_x * spriteX + scene->player.plane_y * spriteY); 

		int spriteScreenX = (int)((scene->r_width / 2) * (1 + transformX / transformY));

		int spriteHeight = abs((int)(scene->r_height / (transformY))); 
		int drawStartY = -spriteHeight / 2 + scene->r_height / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + scene->r_height / 2;
		if(drawEndY >= scene->r_height) drawEndY = scene->r_height - 1;

		int spriteWidth = abs((int) (scene->r_height / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= scene->r_width) drawEndX = scene->r_width - 1;

		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256;
			if(transformY > 0 && stripe > 0 && stripe < scene->r_width && transformY < scene->player.z_buffer[stripe])
				for(int y = drawStartY; y < drawEndY; y++) 
				{
					int d = (y) * 256 - scene->r_height * 128 + spriteHeight * 128; 
					int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
					unsigned int color = *(unsigned int*)(scene->texture[scene->sprites[scene->sprite_order[i]].texture].addr + (texY * scene->texture[scene->sprites[scene->sprite_order[i]].texture].line_length + texX * (scene->texture[scene->sprites[scene->sprite_order[i]].texture].bits_per_pixel / 8))); 
					if((color & 0x00FFFFFF) != 0) my_mlx_pixel_put(img, stripe, y, color);
				}
		}
	}
}
