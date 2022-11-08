/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:46:36 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/11/08 13:40:50 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_double(t_data	*data)
{
	t_tmp	*tmp;
	int		i;

	i = 0;
	if (data->config.w_h[1] == 0)
		return (-4);
	data->config.map = ft_calloc(data->config.w_h[1] + 1, sizeof(char *));
	if (!data->parts)
		return (-4);
	while (data->parts)
	{
		tmp = data->parts->next;
		data->config.map[i] = add_two(data->parts);
		i++;
		data->parts = tmp;
	}
	return (0);
}

int	what_to_do(char *s, t_data *data)
{
	static u8bit	l;
	char			**get_info;

	if (l != 63)
	{
		if (*s == '\n')
		{
			free(s);
			return (0);
		}
		else
		{
			get_info = ft_split(s, 32, NULL);
			if (check_valid(data, &l, get_info))
			{
				free(s);
				return (-4);
			}
			free(s);
		}
		return (0);
	}
	if (l == 63 && load_map(s, data))
		return (-4);
	return (0);
}

int	check_boundries(t_data *data, char **map, size_t i, size_t j)
{
	int	err;

	err = ((i > 0) && ((size_t *)map[i - 1])[0] >= j
			&& not_valid(map[i - 1][j], "1 ") < 0);
	err += ((i + 1 < data->config.w_h[1])
			&& (((size_t *)map[i + 1])[0] >= j)
			&& (not_valid(map[i + 1][j], "1 ") < 0));
	err += ((j > 1) && not_valid(map[i][j - 1], "1 ") < 0);
	err += (not_valid(map[i][j + 1], "1 ") < 0);
	return (err);
}

int	fill_pl(t_data *data, char c, int y, int x)
{
	t_pl	*pl;

	pl = &data->config.plr;
	if (pl->x >= 0 || pl->y >= 0 || pl->d >= 0)
		return (-4);
	pl->x = x * mini_t + (mini_t / 2);
	pl->y = y * mini_t + (mini_t / 2);
	pl->d = c;
	return (0);
}

int	check_map(t_data *data)
{
	size_t		i;
	int			j;
	char		**map;

	i = 0;
	map = data->config.map;
	while (map[i])
	{
		j = SIZE_LEN;
		if (not_valid(map[i][j], "1 ") < 0)
			return (-4);
		while (map[i][j])
		{
			if ((not_valid(map[i][j], "NSWE") >= 0)
				&& fill_pl(data, map[i][j], i, j))
				return (-4);
			if ((i == 0 || i == data->config.w_h[1] - 1)
				&& (not_valid(map[i][j], "1 ") < 0))
				return (-4);
			if (map[i][j] == ' ' && check_boundries(data, map, i, j))
				return (-4);
			j++;
		}
		i++;
	}
	return (-4 * (data->config.plr.x == -1));
}
