#include "cub3d.h"

int	check(char *s, int nu, t_data *data)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'P')
		{
			data->tp.s.y = (nu * 32) + 16 ;
			data->tp.s.x = i * 32 + 16;
		}
		i++;
	}
	return (i);
}

char	**read_map(char	*map_name, int	*max, t_data *data)
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
		if (!map[i])
			break ;
		tmp = check(map[i], i, data);
		max[1] += (tmp - max[1]) * (tmp > max[1]);
		i++;
	}
	return (map);
}