#include "cub3d.h"

void	init(t_info	*gm_info, int *max)
{
	int	s[2];

	s[0] = 32;
	s[1] = 32;
	gm_info->max[0] = max[0];
	gm_info->max[1] = max[1];
	gm_info->pic.p = mlx_xpm_file_to_image(gm_info->mlx, "xpms/player.xpm", &s[0], &s[1]);
	gm_info->pic.mpt = mlx_xpm_file_to_image(gm_info->mlx, "xpms/empty.xpm", &s[0], &s[1]);
	gm_info->pic.wall = mlx_xpm_file_to_image(gm_info->mlx, "xpms/wall.xpm", &s[0], &s[1]);
}

void	check_and_put(int i, int j, t_info *gm_info)
{
	if (gm_info->map[i][j] == '1')
		mlx_put_image_to_window(gm_info->mlx, gm_info->window, gm_info->pic.wall, j * 32, i * 32);
	else if (gm_info->map[i][j] == 'P')
		mlx_put_image_to_window(gm_info->mlx, gm_info->window, gm_info->pic.p, j * 32, i * 32);
	else
		mlx_put_image_to_window(gm_info->mlx, gm_info->window, gm_info->pic.mpt, j * 32, i * 32);
}

//void	draw_map(t_info *gm_info)
//{
//	int	i;
//	int	j;
//	int	len;
//
//	i = 0;
//	while (i < gm_info->max[0])
//	{
//		j = 0;
//		len = ft_strlen(gm_info->map[i]);
//		if (len == -1)
//			break ;
//		while (j < gm_info->max[1])
//		{
//			if (j < len)
//				check_and_put(i, j, gm_info);
//			else
//				mlx_put_image_to_window(gm_info->mlx, gm_info->window, gm_info->pic.mpt, i * 32, j * 32);
//			j++;
//		}
//		i++;
//	}
//}

//void	display_map(char **map, int *max)
//{
//	t_info	gm_info;
//
//	gm_info.mlx = mlx_init();
//	gm_info.map = map;
//	init(&gm_info, max);
//	gm_info.window = mlx_new_window(gm_info.mlx, max[1] * 32, max[0] * 32, "NICE");
//	draw_map(&gm_info);
//	mlx_loop(gm_info.mlx);
//}