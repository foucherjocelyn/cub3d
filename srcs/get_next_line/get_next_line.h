/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:20:42 by jfoucher          #+#    #+#             */
/*   Updated: 2019/11/15 19:36:26 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

void	*ft_memmove(void *dst, const void *src, size_t len);
int		get_next_line(int fd, char **line);
int		ft_strlen(const char *s);
int		ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
