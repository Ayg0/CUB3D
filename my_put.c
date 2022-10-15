#include "cub3d.h"

int	wall_c(int flag, int color)
{
	static int	w_c;

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

int	p_v(int x)
{
	int	mask;

	mask = (x >> 31);
	return ((x ^ mask) - mask);
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
			new->s.x += (d[0] > 0) * 1 + (d[0] < 0) * -1;
		}
		new->s.y += (d[1] >= 0) * 1 + (d[1] < 0) * -1;
	}
	if (!put(new->s.x, new->s.y, img_d, color))
		return (-1);
	return (0);
}

int	draw_line(t_tp t_point, t_img_d *img_d, int color, float p)
{
	int		d[2];
	t_ps	start;

	d[0] = t_point.e.x - t_point.s.x;
	d[1] = t_point.e.y - t_point.s.y;
	start.x = t_point.s.x;
	start.y = t_point.s.y;
	(p_v(d[0]) > p_v(d[1])) && draw_case1(&t_point, d, img_d, color);
	(p_v(d[0]) <= p_v(d[1])) && draw_case2(&t_point, d, img_d, color);
	return (p_v((cos(p) * (t_point.s.x - start.x))
			+ sin(p) * (t_point.s.y - start.y)));
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
			put_block(i, j, get_value(0,
					255 * (gi->map[i][j] != '1'),
					255, 255 * (gi->map[i][j] != '1')), img_d);
			j++;
		}
		i++;
	}	
}

void	draw_map(t_data *all_data)
{
	all_data->inf.map = read_map("./map", all_data->inf.max);
	all_data->img_d.height = all_data->inf.max[0] * 32;
	all_data->img_d.width = all_data->inf.max[1] * 32;
	all_data->s.pic.height = main_h;
	all_data->s.pic.width = main_w;
	all_data->inf.window = mlx_new_window(all_data->inf.mlx, all_data->img_d.width, all_data->img_d.height, "NICE");
	all_data->img_d.img = mlx_new_image(all_data->inf.mlx, all_data->img_d.width, all_data->img_d.height);
	all_data->img_d.p = (int *)mlx_get_data_addr(all_data->img_d.img, &all_data->img_d.b_by_p, &all_data->img_d.size_line, &all_data->img_d.endi);
	all_data->s.window = mlx_new_window(all_data->inf.mlx, main_w, main_h, "other one");
	all_data->s.pic.img = mlx_new_image(all_data->inf.mlx, main_w, main_h);
	all_data->s.pic.p = (int *)mlx_get_data_addr(all_data->s.pic.img, &all_data->s.pic.b_by_p, &all_data->s.pic.size_line, &all_data->s.pic.endi);
	wall_c(1, get_value(0, 0, 255, 0));
	//draw(&all_data->img_d, &all_data->inf);
}

int	manage_keys(int k, t_data *all)
{
	int	new[2];

	new[0] = all->tp.s.x + (((k == w_key) * 20) + ((k == s_key) * -20)) * cos(all->rot)
		+ (((k == a_key) * -20) + ((k == d_key) * 20)) * cos(all->rot + M_PI_2);
	new[1] = all->tp.s.y + (((k == w_key) * 20) + ((k == s_key) * -20)) * sin(all->rot)
		+ (((k == a_key) * -20) + ((k == d_key) * 20)) * sin(all->rot + M_PI_2);
	if (all->img_d.p[new[0] + (new[1] * all->img_d.width)] == wall_c(0, 0))
		return (-1);
	all->tp.s.x = new[0];
	all->tp.s.y = new[1];
	all->rot += ((k == 124) * (M_PI / 6)) + ((k == 123) * (-M_PI / 6));
	return (0);
}

int	draw_sewindow(int x, int distance, int color, t_data *data)
{
	int	y;
	int	nu_pxls;
	int	di;

	if (!distance)
		exit(5);
	nu_pxls = data->cons / distance;
	y = (main_h - nu_pxls) / 2;
	if (y < 0)
		y = 0;
	di = y + nu_pxls;
	while (y < main_h && y < di)
	{
		put_pixel(x, y, &data->s.pic, color);
		y++;
	}
	return (0);
}

int	reset_img(t_data *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < main_h)
	{
		x = 0;
		while (x < main_w)
		{
			if (y > main_h / 2)
			put_pixel(x, y, &all->s.pic, get_value(0, 102, 153, 102));
			else
				put_pixel(x, y, &all->s.pic, get_value(0, 204, 255, 204));
			x++;
		}
		y++;
	}
	return (0);
}

int	do_it(int key, t_data *all)
{
	int		distance = 0;
	int		x;
	float	inc;

	inc = (M_PI / 3) / all->s.pic.width;
	x = 0;
	if (manage_keys(key, all) == -1)
		return (-1);
	draw(&all->img_d, &all->inf);
	reset_img(all);
	float angle = all->rot - (M_PI / 6);
	while (angle < all->rot + (M_PI / 6))
	{
		all->tp.e.y = 4000 * sin(angle);
		all->tp.e.x = 4000 * cos(angle);
		distance = draw_line(all->tp, &all->img_d, get_value(0, 0, 0, 255), all->rot);
		draw_sewindow(x, distance, get_value(0, 67, 225, 69), all);
		angle += inc;
		x++;
	}
	mlx_put_image_to_window(all->inf.mlx,
		all->inf.window, all->img_d.img, 0, 0);
	mlx_put_image_to_window(all->inf.mlx,
		all->s.window, all->s.pic.img, 0, 0);
	return (1);
}

int	main(void)
{
	t_data	all_data;

	all_data.tp.s.y = 100;
	all_data.tp.s.x = 100;
	all_data.cons = 32 * (main_w / 2) / tan(M_PI / 6);
	all_data.rot = 0;
	all_data.inf.mlx = mlx_init();
	draw_map(&all_data);
	mlx_put_image_to_window(all_data.inf.mlx,
		all_data.inf.window, all_data.img_d.img, 0, 0);
	mlx_hook(all_data.s.window, 02, (1L << 0), do_it, &all_data);
	mlx_put_image_to_window(all_data.inf.mlx,
		all_data.s.window, all_data.s.pic.img, 0, 0);
	mlx_loop(all_data.inf.mlx);
}
