#include "cub3d.h"


void	put_pixel(int x, int y, t_img_d *img_data, int color)
{
	img_data->p[x + y * img_data->width] = color;
}

int	get_value(u8bit tr, u8bit red, u8bit blue, u8bit green)
{
	return (tr << 24 | red << 16 | green << 8 | blue);
}

int p_v(int x)
{
    int mask = (x >> 31);
    return (x ^ mask) - mask;
}

int	draw_case1(t_tp new, t_img_d *img_d, int color)
{
	int	dx;
	int	dy;
	int	pk;

	dx = new.e.x - new.s.x;
	dy = new.e.y - new.s.y;
	pk = (2 * dy) - dx;
	while (new.e.x != new.s.x)
	{
		put_pixel(new.s.x, new.s.y, img_d, color);
		//printf("(%d:%d)\n", new.s.x, new.s.y);
		if (pk < 0)
			pk += 2 * dy;
		else
		{
			pk += (2 * dy) - (2 * dx);
			new.s.y++;
		}
		new.s.x++;
	}
	return (0);
}

int	draw_case2(t_tp new, t_img_d *img_d, int color)
{
	int	dx;
	int	dy;
	int	pk;

	dx = new.e.x - new.s.x;
	dy = new.e.y - new.s.y;
	pk = (2 * dx) - dy;
	while (new.e.y != new.s.y)
	{
		put_pixel(new.s.x, new.s.y, img_d, color);
		//printf("(%d:%d)\n", new.s.x, new.s.y);
		if (pk < 0)
			pk += 2 * dx;
		else
		{
			pk += (2 * dx) - (2 * dy);
			new.s.x++;
		}
		new.s.y++;
	}
	return (0);
}

int	hctiws(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
	return (0);
}

int	draw_line(t_tp t_point, t_img_d *img_d, int color)
{
	int		d_x;
	int		d_y;
	int		pr;
	int		m;

	d_x = t_point.e.x - t_point.s.x; 
	d_y = t_point.e.y - t_point.s.y;
	if (p_v(d_x) > p_v(d_y))
		return (((d_x < 0) && hctiws(&t_point.e.x, &t_point.s.x))
			|| draw_case1(t_point, img_d, color));
	(d_y < 0) && hctiws(&t_point.e.y, &t_point.s.y);
	return (draw_case2(t_point, img_d, color));
}

int	main()
{
	t_img_d	img_data;
	int		img[2];
	int		i;
	int		j;
	t_info	gm_info;
	int		color;

	img_data.height = 250;
	img_data.width = 480;
	gm_info.mlx = mlx_init();
	gm_info.window = mlx_new_window(gm_info.mlx, 480, 250, "NICE");
	//gm_info.pic.p = mlx_xpm_file_to_image(gm_info.mlx, "xpms/wall.xpm", &img_data.width, &img_data.height);
	gm_info.pic.p = mlx_new_image(gm_info.mlx, 480, 250);
	img_data.p = mlx_get_data_addr(gm_info.pic.p, &img_data.b_by_p, &img_data.size_line, &img_data.endi);
	t_tp	t_point;

	t_point.s.x = 2;
	t_point.e.x = 140;
	t_point.s.y = 5;
	t_point.e.y = 180;
	draw_line(t_point, &img_data, get_value(0, 255, 255, 255));
	//i ^= i;
	//while (i < img_data.height)
	//{
	//	j ^= j;
	//	while (j < img_data.width)
	//	{
	//		color = get_value(0, 0, 0, 255);
	//		put_pixel(j, i, &img_data, color);
	//		j++;
	//	}
	//	i++;
	//}
	mlx_put_image_to_window(gm_info.mlx, gm_info.window, gm_info.pic.p, 0, 0);
	mlx_loop(gm_info.mlx);
}