/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:36:27 by jfoucher          #+#    #+#             */
/*   Updated: 2021/03/18 22:34:40 by jfoucher         ###   ########.fr       */
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
		error("element missing or invalid");
	parse_map(file, scene);
}

void	p_texture(char *line, char **texture)
{
	int	i;
	int j;

	i = 2;
	j = 0;
	if (*texture)
		error("multiple definitions of the same texture");
	while (line[i] == ' ')
		i++;
	if (!(*texture = malloc(sizeof(char) * (ft_strlen(line) - i + 1))))
		error("malloc error");
	while (line[i])
	{
		(*texture)[j] = line[i];
		i++;
		j++;
	}
	(*texture)[j] = 0;
	if (ft_strlen(*texture) < 5 || !ft_str_at_end(*texture, ".xpm"))
		error("invalid texture");
}

void	p_res(char *line, t_scene *scene)
{
	if ((scene->r_width != 0 || scene->r_height != 0))
		error("multiple resolutions");
	scene->r_width = res_atoi(line);
	scene->r_height = res_atoi(line);
	if (scene->r_width < 1 || scene->r_height < 1)
		error("resolution can't be less than 1");
}

void	p_color(char *line, int *color)
{
	int	i;

	i = 1;
	if (*color != -1)
		error("multiple definitions of the same color");
	*color = (color_atoi(line, &i) << 16);
	*color += (color_atoi(line, &i) << 8);
	*color += color_atoi(line, &i);
}

void	parsing2(char *line, t_scene *scene)
{
	if (line[0] == 'R' && line[1] == ' ')
		p_res(line, scene);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		p_texture(line, &(scene->north));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		p_texture(line, &(scene->south));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		p_texture(line, &(scene->east));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		p_texture(line, &(scene->west));
	else if (line[0] == 'S' && line[1] == ' ')
		p_texture(line, &(scene->sprite));
	else if (line[0] == 'F' && line[1] == ' ')
		p_color(line, &(scene->floor));
	else if (line[0] == 'C' && line[1] == ' ')
		p_color(line, &(scene->ceiling));
	else if (line[0] == '1' || line[0] == ' ')
		count_map_lines(scene, line);
	else if (line[0] == 0 && scene->nb_map_lines > 0)
		error("empty line in map");
	else if (line[0] != 0)
		error("invalid line");
}
