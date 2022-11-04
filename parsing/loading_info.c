/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 09:39:01 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/11/04 09:47:21 by ted-dafi         ###   ########.fr       */
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
// found valid starting word check if already exist;
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
	free(colors);
	free(s);
	if (c[0] < 0 || c[1] < 0 || c[2] < 0)
		return (-4);
	return (get_value(0, c[0], c[2], c[1]));
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
			break;
		i++;
	}
	s[i] = 0;
	return (s);
}

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

int	load_map(char *s, t_data *data)
{
	static t_tmp	*string;
	size_t		size;
	int			*r;
	size_t		i;

	i = 0;
	r = data->config.w_h;
	if (!r[1] && *s != '\n')
	{
		i = 1;
		r[1]++;
	}
	if (*s == '\n' && !r[1])
		free(s);
	else if (*s == '\n' && r[1])
	{
		free(s);
		return (-4);
	}
	if (r[1])
	{
		if (!string)
		{
			string = ft_calloc(1, sizeof(t_tmp));
			data->parts = string;
		}
		else
		{
			string->next = ft_calloc(1, sizeof(t_tmp));
			string = string->next;
		}
		string->tmp = cp_no_nl_check(s, 0);
		if (!string->tmp)
			return (-4);
		r[0] += (r[0] < ft_strlen(string->tmp))
			* (ft_strlen(string->tmp) - r[0]);
		!i && r[1]++;
	}
	return (0);
}

char *add_two(t_tmp *part)
{
	char	*s;
	int		b4;
	int		i;

	b4 = ft_strlen(part->tmp) + 1;
	s = ft_calloc(b4 + 2, sizeof(char));
	s[0] = b4;
	i = 0;
	while (part->tmp[i])
	{
		s[i + 1] = part->tmp[i];
		i++;
	}
	s[i + 1] = 32;
	free(part->tmp);
	free(part);
	return (s);
}

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
	return(0);
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
			{
				free(s);
				return (-4);
			}
			//	print_error(2, "Unvalid Configuration.", 5);
			free(s);
		}
		return (0);
	}
	if (l == 63 && load_map(s, data))
		return (-4);
	return (0);			
}

int	check_boundries(t_data *data, char **map, int i, int j)
{
	int	err;

	err = (i > 0 && map[i - 1][0] >= j) && (not_valid(map[i - 1][j], "1 ") < 0);
	err += (i + 1 < data->config.w_h[1]) && map[i + 1][0] >= j && (not_valid(map[i + 1][j], "1 ") < 0);
	err += (j > 1) && (not_valid(map[i][j - 1], "1 ") < 0);
	err += (not_valid(map[i][j + 1], "1 ") < 0);
	return (err);
}

int	check_map(t_data *data)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = data->config.map;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if ((i == 0 || i == data->config.w_h[1] - 1) && (not_valid(map[i][j], "1 ") < 0))
				return (-4);
			if (map[i][j] == ' ' && check_boundries(data, map, i, j))
				return (-4);
			j++;
		}
		i++;
	}
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
	if (load_double(data))
		return (-4);
	if (check_map(data))
		return (-4);
	printf("%s\n", data->config.no);
	printf("%s\n", data->config.so);
	printf("%s\n", data->config.we);
	printf("%s\n", data->config.ea);
	printf("%d\n", data->config.fc);
	printf("%d\n", data->config.w_h[0]);
	printf("%d\n", data->config.w_h[1]);
	printf("%d\n-------------------\n", data->config.cc);
	int	i;
	i = 0;
	while (data->config.map[i])
	{
		printf("%d,^^%s\n", i, (data->config.map[i] + 1));
		i++;
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
}

int	main(void)
{
	t_data	all_data;

	init_names(&all_data, all_data.config.names);
	initial_reading(&all_data, "map.cub");
	system("leaks a.out");
	//pause();
}
