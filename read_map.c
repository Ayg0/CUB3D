#include "cub3d.h"

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
		if (re <= 0 || (c == '\n' && ft_strlen(master_s)))
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

int	get_size(char *name)
{
	int		f;
	int		i;
	char	*s;

	f = open(name, O_RDONLY);
	if (f < 0)
		return (-1);
	i = 0;
	while (1)
	{
		s = read_line(f);
		if (!s)
			break ;
		i++;
		free(s);
	}
	close(f);
	return (i);
}

char	**read_map(char	*map_name, int	*max)
{
	int	f;
	int	i;
	int	tmp;
	char	**map;

	max[0] = get_size(map_name);
	f = open(map_name, O_RDONLY);
	if (f < 0)
		return (NULL);
	map = ft_calloc(max[0] + 1, sizeof(char *));
	i = 0;
	max[1] = 0;
	while (1)
	{
		map[i] = read_line(f);
		tmp = ft_strlen(map[i]);
		max[1] += (tmp - max[1]) * (tmp > max[1]);
		if (!map[i])
			break ;
		i++;
	}
	return (map);
}