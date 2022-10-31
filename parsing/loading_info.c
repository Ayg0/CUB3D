/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 09:39:01 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/10/31 12:01:13 by ted-dafi         ###   ########.fr       */
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

char	*join_char(char *s, char c)
{
	char	*master_s;
	int		i;

	master_s = ft_calloc(ft_strlen(s) + 2, sizeof(char));
	i = 0;
	while (s[i])
	{
		master_s[i] = s[i];
		i++;
	}
	master_s[i] = c;
	free(s);
	return(master_s);
}

char	*read_line(int fd)
{
	int		re;
	char	c;
	char	*master_s;
	size_t	len;

	re = 1;
	c = 0;
	len = 0;
	master_s = ft_calloc(1, sizeof(char));
	while (re > 0)
	{
		re = read(fd, &c, 1);
		if (re <= 0)
			break ;
		master_s = join_char(master_s, c);
		if (master_s[len] == '\n')
			break;
		len++;
	}
	if (!ft_strlen(master_s))
	{
		free(master_s);
		master_s = NULL;
	}
	return (master_s);
}
// found valid starting word check if already exist if not fill it;

u8bit	deja_vu(u8bit *l, u8bit i)
{
	u8bit	mask = 1;

	mask <<= i;
	if ((*l & mask) == mask)
		return (1);
	*l |= mask;
	return (0);	
}

int	toi(char *str, int flag)
{
	int				i;
	int				sign;
	unsigned long	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	if (!flag)
		free(str);
	return (num * sign);
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

	colors = ft_split(s, ',');
	if (double_len(colors) != 3)
		return (-4);
	c[0] = toi(colors[0], 0);
	c[1] = toi(colors[1], 0);
	c[2] = toi(colors[2], 0);
	if (c[0] < 0 || c[1] < 0 || c[2] < 0)
		return (-4);
	return (get_value(0,c[0], c[2], c[1]));
}

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
	u8bit deja_v;

	if (deja_vu(l, i))
		return (-4);
	load_param(data, i, s);
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

u8bit	check_valid(t_data	*data, u8bit *l, char **s)
{
	u8bit	i;
	u8bit	size;

	i = 0;
	size = double_len(s);
	while (size == 2 && data->config.names[i])
	{
		if (!(ft_strcmp(s[0], data->config.names[i])))
			return (fill_param(data, l, i, s[1]));
		i++;
	}
	return (!(!(*l)));
}

int	load_map(t_data *data)
{
	printf("%s\n", data->config.no);
	printf("%s\n", data->config.so);
	printf("%s\n", data->config.we);
	printf("%s\n", data->config.ea);
	printf("%d\n", data->config.fc);
	printf("%d\n", data->config.cc);
	exit(write(1, "a fin a mol l map\n", 18));	
}

int	what_to_do(char *s, t_data *data)
{
	static	u8bit	l;
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
			get_info = ft_split(s, 32);
			if (check_valid(data, &l, get_info))
				return (-4);
		}
	}
	l == 63 && load_map(data);
	return (0);			
}

int	get_content(int fd, t_data *data)
{
	char	*s;
	while (1)
	{
		s = read_line(fd);
		if (!s)
			break;
		if (what_to_do(s, data) < 0)
			return (-3); 
	}
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
	int err;

	err = check_map_name(map_name, ".cub");
	printf("%d\n", err);
	err = load_info(data, err, map_name);
	printf("%d\n", err);
	/*
		map double pointer
	*/
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
	data->config.cc = 0;
	data->config.fc = 0;
}

int	main(void)
{
	t_data	all_data;

	init_names(&all_data, all_data.config.names);
	initial_reading(&all_data, "map.cub");
}
