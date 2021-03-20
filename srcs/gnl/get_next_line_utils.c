/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 20:55:22 by jfoucher          #+#    #+#             */
/*   Updated: 2019/11/12 22:04:19 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = (src > dst) ? 0 : len - 1;
	while ((dst || src) && i < len && i >= 0)
	{
		((unsigned char*)dst)[i] = ((const unsigned char*)src)[i];
		i = (src > dst) ? i + 1 : i - 1;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (0);
	while (i < ft_strlen(s1) && s1[i] != '\n')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return ((!s1) ? ft_strdup(s2) : ft_strdup(s1));
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	while (i < ft_strlen(s1))
	{
		s3[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2) && s2[i - ft_strlen(s1)] != '\n')
	{
		s3[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	s3[i] = 0;
	return (s3);
}
