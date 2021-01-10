/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:46:41 by jfoucher          #+#    #+#             */
/*   Updated: 2019/10/19 04:14:04 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void		freeall(char **strs)
{
	int		i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char		**ssalloc(char const *s, char c)
{
	char	**strs;
	int		i;
	int		size;

	i = 0;
	size = 1;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
		size++;
	}
	strs = ft_calloc(1, sizeof(char *) * size);
	if (!strs)
		return (0);
	return (strs);
}

static int		salloc(char **strs, char const *s, char c)
{
	int	i;
	int	j;
	int k;

	i = 0;
	j = 0;
	while (s[j] && s[j] == c)
		j++;
	while (s[j])
	{
		k = 0;
		while (s[j] && s[j] != c)
		{
			j++;
			k++;
		}
		strs[i] = ft_calloc(1, sizeof(char) * (k + 1));
		if (!strs[i])
			return (0);
		i++;
		while (s[j] && s[j] == c)
			j++;
	}
	return (1);
}

static void		fill(char **strs, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[j] && s[j] == c)
		j++;
	while (s[j])
	{
		k = 0;
		while (s[j] && s[j] != c)
		{
			strs[i][k] = s[j];
			j++;
			k++;
		}
		strs[i][k] = 0;
		while (s[j] && s[j] == c)
			j++;
		i++;
	}
	strs[i] = 0;
}

char			**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (0);
	strs = ssalloc(s, c);
	if (!strs)
		return (0);
	if (!salloc(strs, s, c))
	{
		freeall(strs);
		return (0);
	}
	fill(strs, s, c);
	return (strs);
}
