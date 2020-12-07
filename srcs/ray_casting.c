#include "cub3d.h"

//arrays used to sort the sprites
int *spriteOrder;
double *spriteDistance;

//function used to sort the sprites
void sortSprites(int* order, double* dist, int amount);

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_press(int keycode)
{
	//move forward if no wall in front of you
	if (keycode == 119)
	{
		if(g_world_map[(int)(g_p.pos_x + g_p.dir_x * g_p.move_speed)][(int)g_p.pos_y] != 1) g_p.pos_x += g_p.dir_x * g_p.move_speed;
		if(g_world_map[(int)g_p.pos_x][(int)(g_p.pos_y + g_p.dir_y * g_p.move_speed)] != 1) g_p.pos_y += g_p.dir_y * g_p.move_speed;
	}
	//move backwards if no wall behind you
	if (keycode == 115)
	{
		if(g_world_map[(int)(g_p.pos_x - g_p.dir_x * g_p.move_speed)][(int)g_p.pos_y] != 1) g_p.pos_x -= g_p.dir_x * g_p.move_speed;
		if(g_world_map[(int)g_p.pos_x][(int)(g_p.pos_y - g_p.dir_y * g_p.move_speed)] != 1) g_p.pos_y -= g_p.dir_y * g_p.move_speed;
	}
	//move to the left if no wall behind you
	if (keycode == 97)
	{
		if(g_world_map[(int)(g_p.pos_x - g_p.plane_x * g_p.move_speed)][(int)g_p.pos_y] != 1) g_p.pos_x -= g_p.plane_x * g_p.move_speed;
		if(g_world_map[(int)g_p.pos_x][(int)(g_p.pos_y - g_p.plane_y * g_p.move_speed)] != 1) g_p.pos_y -= g_p.plane_y * g_p.move_speed;
	}
	//move to the right if no wall behind you
	if (keycode == 100)
	{
		if(g_world_map[(int)(g_p.pos_x + g_p.plane_x * g_p.move_speed)][(int)g_p.pos_y] != 1) g_p.pos_x += g_p.plane_x * g_p.move_speed;
		if(g_world_map[(int)g_p.pos_x][(int)(g_p.pos_y + g_p.plane_y * g_p.move_speed)] != 1) g_p.pos_y += g_p.plane_y * g_p.move_speed;
	}
	//rotate to the right
	if (keycode == 65363)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = g_p.dir_x;
		g_p.dir_x = g_p.dir_x * cos(-g_p.rot_speed) - g_p.dir_y * sin(-g_p.rot_speed);
		g_p.dir_y = oldDirX * sin(-g_p.rot_speed) + g_p.dir_y * cos(-g_p.rot_speed);
		double oldPlaneX = g_p.plane_x;
		g_p.plane_x = g_p.plane_x * cos(-g_p.rot_speed) - g_p.plane_y * sin(-g_p.rot_speed);
		g_p.plane_y = oldPlaneX * sin(-g_p.rot_speed) + g_p.plane_y * cos(-g_p.rot_speed);
	}
	//rotate to the left
	if (keycode == 65361)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = g_p.dir_x;
		g_p.dir_x = g_p.dir_x * cos(g_p.rot_speed) - g_p.dir_y * sin(g_p.rot_speed);
		g_p.dir_y = oldDirX * sin(g_p.rot_speed) + g_p.dir_y * cos(g_p.rot_speed);
		double oldPlaneX = g_p.plane_x;
		g_p.plane_x = g_p.plane_x * cos(g_p.rot_speed) - g_p.plane_y * sin(g_p.rot_speed);
		g_p.plane_y = oldPlaneX * sin(g_p.rot_speed) + g_p.plane_y * cos(g_p.rot_speed);
	}
	if (keycode == 65307)
		exit(0);
	return(0);
}

int		render(t_data *texture)
{
	int w = g_s.r_width;
	int h = g_s.r_height;
	t_data img;

	spriteOrder = malloc(sizeof(int) * g_s.nb_sprites);
	spriteDistance = malloc(sizeof(double) * g_s.nb_sprites);
	img.img = mlx_new_image(g_ptr.mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for(int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayDirX = g_p.dir_x + g_p.plane_x * cameraX;
		double rayDirY = g_p.dir_y + g_p.plane_y * cameraX;
		//which box of the map we're in
		int mapX = (int)g_p.pos_x;
		int mapY = (int)g_p.pos_y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (g_p.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - g_p.pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (g_p.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - g_p.pos_y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
				if (mapX < (int)g_p.pos_x)
					side = 1;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 2;
				if (mapY < (int)g_p.pos_y)
					side = 3;
			}
			//Check if ray has hit a wall
			if (g_world_map[mapX][mapY] == 1) hit = 1;
		} 
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side < 2) perpWallDist = (mapX - g_p.pos_x + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - g_p.pos_y + (1 - stepY) / 2) / rayDirY;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);
		if (perpWallDist < 0.000001)
			lineHeight = 2147483647;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;
		//texturing calculations

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side < 2) wallX = g_p.pos_y + perpWallDist * rayDirY;
		else           wallX = g_p.pos_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)TEX_WIDTH);
		if(side < 2 && rayDirX > 0) texX = TEX_WIDTH - texX - 1;
		if(side >= 2 && rayDirY < 0) texX = TEX_WIDTH - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TEX_HEIGHT / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
			int texY = (int)texPos & (TEX_HEIGHT - 1);
			texPos += step;
			unsigned int color = *(unsigned int*)(texture[side].addr + (texY * texture[side].line_length + texX * (texture[side].bits_per_pixel / 8)));
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//			if(side == 1) color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&img, x, y, color);
		}
		for(int y = 0; y<drawStart; y++)
			my_mlx_pixel_put(&img, x, y, 0x0000FF);
		for(int y = drawEnd; y<h; y++)
			my_mlx_pixel_put(&img, x, y, 0xBBBBBB);
		//SET THE ZBUFFER FOR THE SPRITE CASTING
		g_p.z_buffer[x] = perpWallDist; //perpendicular distance is used
	}

	//SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < g_s.nb_sprites; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((g_p.pos_x - g_s.sprites[i].x) * (g_p.pos_x - g_s.sprites[i].x) + (g_p.pos_y - g_s.sprites[i].y) * (g_p.pos_y - g_s.sprites[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(spriteOrder, spriteDistance, g_s.nb_sprites);

	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < g_s.nb_sprites; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = g_s.sprites[spriteOrder[i]].x - g_p.pos_x;
		double spriteY = g_s.sprites[spriteOrder[i]].y - g_p.pos_y;

		//transform sprite with the inverse camera matrix
		// [ g_p.plane_x   g_p.dir_x ] -1                                       [ g_p.dir_y      -g_p.dir_x ]
		// [               ]       =  1/(g_p.plane_x*g_p.dir_y-g_p.dir_x*g_p.plane_y) *   [                 ]
		// [ g_p.plane_y   g_p.dir_y ]                                          [ -g_p.plane_y  g_p.plane_x ]

		double invDet = 1.0 / (g_p.plane_x * g_p.dir_y - g_p.dir_x * g_p.plane_y); //required for correct matrix multiplication

		double transformX = invDet * (g_p.dir_y * spriteX - g_p.dir_x * spriteY);
		double transformY = invDet * (-g_p.plane_y * spriteX + g_p.plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + h / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + h / 2;
		if(drawEndY >= h) drawEndY = h - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int) (h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= w) drawEndX = w - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) g_p.z_buffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < w && transformY < g_p.z_buffer[stripe])
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
					unsigned int color = *(unsigned int*)(texture[g_s.sprites[spriteOrder[i]].texture].addr + (texY * texture[g_s.sprites[spriteOrder[i]].texture].line_length + texX * (texture[g_s.sprites[spriteOrder[i]].texture].bits_per_pixel / 8))); //get current color from the texture
					if((color & 0x00FFFFFF) != 0) my_mlx_pixel_put(&img, stripe, y, color);//paint pixel if it isn't black, black is the invisible color
				}
		}
	}
	mlx_put_image_to_window(g_ptr.mlx, g_ptr.win, img.img, 0, 0);
	mlx_destroy_image(g_ptr.mlx, img.img);
	free(spriteOrder);
	free(spriteDistance);
	return(0);
}

void	load_image(t_data *img, char *path)
{
	img->img = mlx_xpm_file_to_image(g_ptr.mlx, path, &img->w, &img->h);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length), &(img->endian));
}

//sort algorithm
//sort the sprites based on distance
void sortSprites(int* order, double* dist, int amount)
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
