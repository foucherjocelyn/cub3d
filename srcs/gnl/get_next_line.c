/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:19:18 by jfoucher          #+#    #+#             */
/*   Updated: 2019/11/15 18:39:09 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static	char	buff[BUFFER_SIZE + 1] = "\0";
	char			*tmp;
	int				rd;
	int				eol;

	rd = 1;
	if (!line || BUFFER_SIZE < 1)
		return (-1);
	if (!(*line = ft_strjoin(0, buff)))
		return (-1);
	while ((eol = ft_strchr(buff, '\n')) == -1 && rd > 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
			return (-1);
		buff[rd] = 0;
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free(tmp);
		if (!*line)
			return (-1);
	}
	if (eol > -1)
		ft_memmove(buff, &buff[eol + 1], BUFFER_SIZE - eol);
	return ((rd > 0) ? 1 : rd);
}
