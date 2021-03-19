/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:36:27 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/19 15:37:43 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing(char *file, t_scene *scene)
{
	char	*line;
	int		fd;

	scene->nb_map_lines = 0;
	init_parsing(scene);
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		parsing2(line, scene);
		free(line);
	}
	free(line);
	close(fd);
	if (!scene->r_width || !scene->r_height || !scene->north || !scene->south
			|| !scene->west || !scene->east || !scene->sprite
			|| scene->floor == -1 || scene->ceiling == -1)
		error(scene, "element missing or invalid");
	parse_map(file, scene);
}

void	p_texture(t_scene *scene, char *line, char **texture)
{
	int	i;
	int j;

	i = 2;
	j = 0;
	if (*texture)
	{
		free(line);
		error(scene, "multiple definitions of the same texture");
	}
	while (line[i] == ' ')
		i++;
	if (!(*texture = malloc(sizeof(char) * (ft_strlen(line) - i + 1))))
		error(scene, "malloc error");
	while (line[i])
	{
		(*texture)[j++] = line[i];
		i++;
	}
	(*texture)[j] = 0;
	if (ft_strlen(*texture) < 5 || !ft_str_at_end(*texture, ".xpm"))
	{
		free(line);
		error(scene, "invalid texture");
	}
}

void	p_res(char *line, t_scene *scene)
{
	if ((scene->r_width != 0 || scene->r_height != 0))
	{
		free(line);
		error(scene, "multiple resolutions");
	}
	scene->r_width = res_atoi(scene, line);
	scene->r_height = res_atoi(scene, line);
	if (scene->r_width < 1 || scene->r_height < 1)
	{
		free(line);
		error(scene, "resolution can't be less than 1");
	}
}

void	p_color(t_scene *scene, char *line, int *color)
{
	int	i;

	i = 1;
	if (*color != -1)
	{
		free(line);
		error(scene, "multiple definitions of the same color");
	}
	*color = (color_atoi(scene, line, &i) << 16);
	*color += (color_atoi(scene, line, &i) << 8);
	*color += color_atoi(scene, line, &i);
}

void	parsing2(char *line, t_scene *scene)
{
	if (line[0] == 'R' && line[1] == ' ')
		p_res(line, scene);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		p_texture(scene, line, &(scene->north));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		p_texture(scene, line, &(scene->south));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		p_texture(scene, line, &(scene->east));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		p_texture(scene, line, &(scene->west));
	else if (line[0] == 'S' && line[1] == ' ')
		p_texture(scene, line, &(scene->sprite));
	else if (line[0] == 'F' && line[1] == ' ')
		p_color(scene, line, &(scene->floor));
	else if (line[0] == 'C' && line[1] == ' ')
		p_color(scene, line, &(scene->ceiling));
	else if (line[0] == '1' || line[0] == ' ')
		count_map_lines(scene, line);
	else if (line[0] == 0 && scene->nb_map_lines > 0)
		free_and_error(scene, "empty line in map", line);
	else if (line[0] != 0)
		free_and_error(scene, "invalid line", line);
}
