/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:41:30 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/11/06 09:36:05 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*join_char(char *s, char c)
{
	char		*master_s;
	size_t		i;

	master_s = ft_calloc(ft_strlen(s) + 2, sizeof(char));
	i = 0;
	while (s[i])
	{
		master_s[i] = s[i];
		i++;
	}
	master_s[i] = c;
	free(s);
	return (master_s);
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
			break ;
		len++;
	}
	if (!ft_strlen(master_s))
	{
		free(master_s);
		master_s = NULL;
	}
	return (master_s);
}

char	*add_two(t_tmp *part)
{
	char		*s;
	size_t		b4;
	size_t		i;

	b4 = ft_strlen(part->tmp) + 8;
	s = ft_calloc(b4 + 2, sizeof(char));
	((size_t *)s)[0] = b4;
	i = 0;
	while (part->tmp[i])
	{
		s[i + 8] = part->tmp[i];
		i++;
	}
	s[i + 1] = 32;
	free(part->tmp);
	free(part);
	return (s);
}

int	strtlist(char *s, t_data *data, t_tmp **string, size_t *r)
{
	if (!(*string))
	{
		(*string) = ft_calloc(1, sizeof(t_tmp));
		data->parts = (*string);
	}
	else
	{
		(*string)->next = ft_calloc(1, sizeof(t_tmp));
		(*string) = (*string)->next;
	}
	(*string)->tmp = cp_no_nl_check(s, 0);
	if (!(*string)->tmp)
		return (-4);
	r[0] += (r[0] < ft_strlen((*string)->tmp))
		* (ft_strlen((*string)->tmp) - r[0]);
	return (0);
}

int	load_map(char *s, t_data *data)
{
	static t_tmp		*string;
	size_t				*r;
	size_t				i;

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
		if (strtlist(s, data, &string, r))
			return (-4);
		!i && r[1]++;
	}
	return (0);
}
