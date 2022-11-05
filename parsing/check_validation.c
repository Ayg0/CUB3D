/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:39:38 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/11/05 13:43:44 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_param(t_data *data, u8bit i, char *s)
{
	(i == 0) && (data->config.no = s);
	(i == 1) && (data->config.so = s);
	(i == 2) && (data->config.we = s);
	(i == 3) && (data->config.ea = s);
	(i == 4) && (data->config.fc = get_color(s));
	if (data->config.fc == -4)
		return (-4);
	(i == 5) && (data->config.cc = get_color(s));
	if (data->config.cc == -4)
		return (-4);
	return (0);
}

int	fill_param(t_data *data, u8bit *l, u8bit i, char *s)
{
	if (deja_vu(l, i))
		return (-4);
	if (load_param(data, i, s))
		return (-4);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*q1;
	unsigned char	*q2;

	q1 = (unsigned char *)s1;
	q2 = (unsigned char *)s2;
	i = 0;
	while (q1[i] == q2[i] && q1[i] && q2[i])
		i++;
	return (q1[i] - q2[i]);
}

int	not_valid(char c, char *options)
{
	int	i;

	i = 0;
	while (options[i])
	{
		if (c == options[i])
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char	*cp_no_nl_check(char *s, int flag)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (flag == 0 && (not_valid(s[i], "NSEW01 \n") < 0))
		{
			free(s);
			return (NULL);
		}
		if (s[i] == '\n')
			break ;
		i++;
	}
	s[i] = 0;
	return (s);
}
