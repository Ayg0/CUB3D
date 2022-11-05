/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:44:33 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/11/05 13:45:15 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map_name(char *m_name, char *exten)
{
	int	len;

	len = ft_strlen(m_name) - ft_strlen(exten);
	while (m_name[len] && *exten)
	{
		if (m_name[len] != *exten)
			return (-1);
		exten++;
		len++;
	}
	return (0 * !(*exten) + (-1 * !(!(*exten))));
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

// found valid starting word check if already exist;
u8bit	deja_vu(u8bit *l, u8bit i)
{
	u8bit	mask;

	mask = 1;
	mask <<= i;
	if ((*l & mask) == mask)
		return (1);
	*l |= mask;
	return (0);
}

int	double_len(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	get_color(char *s)
{
	char	**colors;
	u8bit	c[3];
	int		flag;

	flag = 0;
	colors = ft_split(s, ',', &flag);
	if (flag != 2)
		return (-4);
	if (double_len(colors) != 3)
		return (-4);
	c[0] = toi(colors[0], 0);
	c[1] = toi(colors[1], 0);
	c[2] = toi(colors[2], 0);
	free(colors);
	free(s);
	if (c[0] < 0 || c[1] < 0 || c[2] < 0)
		return (-4);
	return (get_value(0, c[0], c[2], c[1]));
}
