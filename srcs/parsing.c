#include "cub3d.h"

void	parsing(char *file, t_scene *scene)
{
	char	*line;
	int		fd;

	scene->nb_map_lines = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		parsing2(line, scene);
		free(line);
	}
	free(line);
	close(fd);
	parse_map(file, scene);
}

void	p_texture(char *line, char **texture)
{
	int	i;
	int j;

	i = 2;
	j = 0;
	while (line[i] == ' ')
		i++;
	*texture = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	while (line[i])
	{
		(*texture)[j] = line[i];
		i++;
		j++;
	}
	(*texture)[j] = 0;
}

void	p_res(char *line, t_scene *scene)
{
	scene->r_width = res_atoi(line);
	scene->r_height = res_atoi(line);
}

void	p_color(char *line, int *color)
{
	int	i;

	i = 1;
	*color = (color_atoi(line, &i) << 16);
	*color += (color_atoi(line, &i) << 8);
	*color += color_atoi(line, &i);
}
void	parsing2(char *line, t_scene *scene)
{
	if (line[0] == 'R')
		p_res(line, scene);
	else if (line[0] == 'N' && line[1] == 'O')
		p_texture(line, &scene->north);
	else if (line[0] == 'S' && line[1] == 'O')
		p_texture(line, &scene->south);
	else if (line[0] == 'E' && line[1] == 'A')
		p_texture(line, &scene->east);
	else if (line[0] == 'W' && line[1] == 'E')
		p_texture(line, &scene->west);
	else if (line[0] == 'S')
		p_texture(line, &scene->sprite);
	else if (line[0] == 'F')
		p_color(line, &scene->floor);
	else if (line[0] == 'C')
		p_color(line, &scene->ceiling);
	else if (line[0] != '\0')
		count_map_lines(scene, line);
}
