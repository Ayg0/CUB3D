/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 10:40:46 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/11/05 10:11:26 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static size_t	tha_nambar(char const *s, char c, int *flag)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
		{
			flag && (*flag)++;
			s++;
		}
		if (!*s)
			break ;
		while (*s != c && *s)
			s++;
		i++;
	}
	return (i);
}

static char	*ft_look_for(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char )c)
			return ((char *)s);
		s++;
	}
	return ((char *)s);
}

static void	why_r_ya_running(char **d, int i)
{
	while (i >= 0)
	{
		free(*d);
		d++;
		i--;
	}
	free(d);
}
// note that dest has to be allocated with calloc, or you should add '\0'
void	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
	}
}

static void	doo_it(char **da, char const *from, char c)
{
	size_t	w;
	int		i;

	i = 0;
	while (*from)
	{
		while (*from == c)
			from++;
		if (*from)
		{
			w = (size_t)(ft_look_for(from, c) - (char *)from);
			*da = (char *)ft_calloc((w + 1), sizeof(char));
			if (!da)
			{
				why_r_ya_running(da, i);
				return ;
			}
			ft_strlcpy(*da, from, w + 1);
			da++;
			i++;
			from += w;
		}
	}
}

char	**ft_split(char const *s, char c, int *flag)
{
	char	**p;

	if (!s)
		return (NULL);
	p = (char **)ft_calloc((tha_nambar(s, c, flag) + 1), sizeof(char *));
	if (!p)
		return (NULL);
	doo_it(p, s, c);
	return (p);
}