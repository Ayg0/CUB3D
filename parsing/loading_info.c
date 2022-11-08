/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 09:39:01 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/11/08 13:53:08 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

u8bit	check_valid(t_data	*data, u8bit *l, char **s)
{
	u8bit	i;
	u8bit	size;
	char	*str;

	i = 0;
	str = s[1];
	size = double_len(s);
	while (size == 2 && data->config.names[i])
	{
		if (!(ft_strcmp(s[0], data->config.names[i])))
		{
			free(s[0]);
			free(s);
			return (fill_param(data, l, i, cp_no_nl_check(str, 1)));
		}
		i++;
	}
	i = 0;
	while (i < size)
		free(s[i++]);
	free(s);
	return (!(!(*l)));
}

int	get_content(int fd, t_data *data)
{
	char	*s;

	while (1)
	{
		s = read_line(fd);
		if (!s)
			break ;
		if (what_to_do(s, data) < 0)
			return (-3);
	}
	close(fd);
	if (load_double(data))
		return (-4);
	if (check_map(data))
		return (-4);
	return (0);
}

int	load_info(t_data *data, int err, char *map_name)
{
	int	fd;

	if (err)
		return (err);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (-2);
	if (get_content(fd, data))
		return (-3);
	return (0);
}

int	initial_reading(t_data *data, char *map_name)
{
	int	err;

	err = check_map_name(map_name, ".cub");
	err = load_info(data, err, map_name);
	printf("--------------------------\n%d\n", err);
	return (err);
}

void	init_names(t_data *data, char **names)
{
	names[0] = "NO";
	names[1] = "SO";
	names[2] = "WE";
	names[3] = "EA";
	names[4] = "F";
	names[5] = "C";
	names[6] = NULL;
	data->config.w_h[0] = 0;
	data->config.w_h[1] = 0;
	data->config.cc = 0;
	data->config.fc = 0;
	data->config.plr.x = -1;
	data->config.plr.y = -1;
	data->config.plr.d = -1;
}

int	main(void)
{
	//t_data	all_data;
//
	//init_names(&all_data, all_data.config.names);
	//if (initial_reading(&all_data, "map.cub"))
	//	return (-4);
	//int	i, j;
	//i = 0;
	//char **map = all_data.config.map;
	//while (map[i])
	//{
	//	printf("%lu\n", ((size_t *)map[i])[0]);
	//	i++;
	//}
	printf("w");
	write(1, "r", 1);
}