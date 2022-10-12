#include "cub3d.h"


int	wall_c(int flag, int color)
{
	static	int	w_c;

	w_c = (color * (flag == 1)) + (w_c * (flag == 0));
	return (w_c);
}

int	put_pixel(int x, int y, t_img_d *img_data, int color)
{
	img_data->p[x + y * img_data->width] = color;
	return (1);
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

int	put(int x, int y, t_img_d *img_d, int color)
{
	if (x >= img_d->width || y >= img_d->height
		|| img_d->p[x + (y * img_d->width)] == wall_c(0, 0))
		return (0);
	return (put_pixel(x, y, img_d, color));	
}

int	draw_case1(t_tp *new, int *d, t_img_d *img_d, int color)
{
	int	dx;
	int	dy;
	int	pk;

	dx = p_v(new->e.x - new->s.x);
	dy = p_v(new->e.y - new->s.y);
	pk = (2 * dy) - dx;
	while (new->e.x != new->s.x && (new->s.x < img_d->width))
	{
		if (!put(new->s.x, new->s.y, img_d, color))
			return (-1);
		if (pk < 0)
			pk += (2 * dy);
		else
		{
			pk += (2 * dy) - (2 * dx);
			new->s.y += (d[1] >= 0) * 1 + (d[1] < 0) * -1;
		}
		new->s.x += (d[0] >= 0) * 1 + (d[0] < 0) * -1;
	}
	if (!put(new->s.x, new->s.y, img_d, color))
		return (-1);
	return (0);
}

int	draw_case2(t_tp *new, int *d, t_img_d *img_d, int color)
{
	int	dx;
	int	dy;
	int	pk;

	dx = p_v(new->e.x - new->s.x);
	dy = p_v(new->e.y - new->s.y);
	pk = (2 * dx) - dy;
	while (new->e.y != new->s.y && (new->s.y < img_d->height))
	{
		if (!put(new->s.x, new->s.y, img_d, color))
			return (-1);
		if (pk < 0)
			pk += 2 * dx;
		else
		{
			pk += (2 * dx) - (2 * dy);
			new->s.x += (d[0] > 0) * 1 + (d[0] < 0) * -1;;
		}
		new->s.y += (d[1] >= 0) * 1 + (d[1] < 0) * -1;;
	}
	if (!put(new->s.x, new->s.y, img_d, color))
		return (-1);
	return (0);
}

int	draw_line(t_tp t_point, t_img_d *img_d, int color)
{
	int		d[2];

	d[0] = t_point.e.x - t_point.s.x; 
	d[1] = t_point.e.y - t_point.s.y;
	if (p_v(d[0]) > p_v(d[1]))
		return (draw_case1(&t_point, d, img_d, color));
	return (draw_case2(&t_point, d, img_d, color));
}

void	put_block(int i, int j, int color, t_img_d *img_d)
{
	int	k;
	int	l;
	k = i * 32;
	i = (i * 32) + 32;
	while (k < i)
	{
		l = j * 32;
		while (l < (j * 32) + 32)
		{
			put_pixel(l, k, img_d, color);
			l++;
		}
		k++;
	}
}

void	draw(t_img_d *img_d, t_info *gi)
{
	int	i;
	int	j;
	i = 0;
	while (i < (img_d->height / 32))
	{
		j = 0;
		while (j < (img_d->width / 32))
		{
			put_block(i, j, get_value(0, 255 * (gi->map[i][j] != '1'), 255, 255 * (gi->map[i][j] != '1')), img_d);
			j++;
		}
		i++;
	}	
}

void	draw_map(t_img_d *img_d, t_info *gi)
{
	gi->map = read_map("./map", gi->max);
	img_d->height = gi->max[0] * 32;
	img_d->width = gi->max[1] * 32;
	gi->window = mlx_new_window(gi->mlx, img_d->width, img_d->height, "NICE");
	gi->pic.p = mlx_new_image(gi->mlx, img_d->width, img_d->height);
	img_d->p = (int *)mlx_get_data_addr(gi->pic.p, &img_d->b_by_p, &img_d->size_line, &img_d->endi);
	wall_c(1, get_value(0, 0, 255, 0));
	draw(img_d, gi);
}

int	manage_keys(int k, t_data *all)
{
	all->tp.s.x += ((k == 13) * -20) + ((k == 2) * 20);
	all->tp.s.y += ((k == 0) * -20) + ((k == 1) * 20);
	all->rot += ((k == 124) * -0.4188) + ((k == 123) * 0.4188);
	return (0);
}

int	do_it(int key, t_data *all)
{
	float	p;

	p = 0;
	draw(&all->img_d, &all->inf);
	manage_keys(key, all);
	while (p < 1.04)
	{
		all->tp.e.x = 4000 * sin(p + all->rot);
		all->tp.e.y = 4000 * cos(p + all->rot);
		draw_line(all->tp, &all->img_d, get_value(0, 0, 0, 255));
		p += 0.05;
	}
	mlx_put_image_to_window(all->inf.mlx, all->inf.window, all->inf.pic.p, 0, 0);
	return (1);
}

int	main()
{
	t_img_d	img_data;
	t_info	gm_info;
	t_data	all_data;

	all_data.tp.s.y = 100;
	all_data.tp.s.x = 100;
	all_data.rot = 0;
	gm_info.mlx = mlx_init();
	draw_map(&img_data, &gm_info);
	all_data.img_d = img_data;
	all_data.inf = gm_info;
	mlx_put_image_to_window(all_data.inf.mlx, all_data.inf.window, all_data.inf.pic.p, 0, 0);
	mlx_key_hook(all_data.inf.window, do_it, &all_data);
	mlx_loop(all_data.inf.mlx);
}