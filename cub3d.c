#include "cub3d.h"

int	main(int ac, char **av)
{
	char *s;
	char	**map;
	int		max[2];

	if (ac != 2)
		return (1);
	map = read_map(av[1], max);
	//check_map()
	display_map(map, max);
}