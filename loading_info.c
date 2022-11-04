/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 09:39:01 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/11/03 10:45:07 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	re = 1;
	c = 0;
	master_s = ft_calloc(1, sizeof(char));
	while (re > 0)
	{
		re = read(fd, &c, 1);
		if (re <= 0 || c == '\n')
			break ;
		master_s = join_char(master_s, c);
	}
	if (!ft_strlen(master_s))
	{
		free(master_s);
		master_s = NULL;
	}
	return (master_s);
}
// found valid starting word check if already exist if not fill it;
int	fill_param(t_data *data, u8bit *l, u8bit i, char *s)
{
	u8bit	deja_vu;

}

u8bit	double_len(char **s)
{
	u8bit	i;

	i = 0;
	while (s[i])
		i++;
	return (i);	
}

int	check_valid(t_data	*data, u8bit *l, char **s)
{
	u8bit	i;
	u8bit	size;

	i = 0;
	size = double_len(s);
	while (size == 2 && data->config.names[i])
	{
		if (s[0] == data->config.names[i])
			return (fill_param(data, l, i, s[1]));
		i++;
	}
	return (!(!(*l)));
}

int	what_to_do(char *s, t_data *data)
{
	static	u8bit	l = 63;
	char			**get_info;

	while (l)
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
			
}

int	get_content(int fd, t_data *data)
{
	char	*s;
	while (1)
	{
		s = read_line(fd);
		if (!s)
			break;
		what_to_do(s, data); 
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
	err = check_map_name(map_name, ".cub");
	printf("%d\n", err);
	err = load_info(data, err, map_name);
	/*
		=> read the whole map
		=> examine all values
		=> map in double pointer
	*/
	return (err);
}

int	main(void)
{
	t_data	all_data;

	initial_reading(&all_data, "map.cub");
}
