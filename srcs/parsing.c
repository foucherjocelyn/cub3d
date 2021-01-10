#include "cub3d.h"

void	parsing(char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		printf("%s\n", line);
		free(line);
	}
	free(line);
}

