#include "cub3d.h"

int	put_pixel(int x, int y, t_img_d *img_data, int color)
{
	img_data->p[x + y * img_data->width] = color;
	return (1);
}

double	p_vf(double value)
{
	return (value * (value >= 0) + -value * (value < 0));
}

int	p_v(int value)
{
	return (value * (value >= 0) + -value * (value < 0));
}

int	put(int x, int y, t_img_d *img_d, int color)
{
	if (x < 0 || y < 0 || x >= img_d->width || y >= img_d->height)
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

//double	draw_line(t_tp t_point, t_img_d *img_d, int color, double p)
//{
//	int		d[2];
//	t_ps	start;
//
//	d[0] = t_point.e.x - t_point.s.x;
//	d[1] = t_point.e.y - t_point.s.y;
//	start.x = t_point.s.x;
//	start.y = t_point.s.y;
//	(p_v(d[0]) > p_v(d[1])) && draw_case1(&t_point, d, img_d, color);
//	(p_v(d[0]) <= p_v(d[1])) && draw_case2(&t_point, d, img_d, color);
//	return (p_vf((cos(p) * (t_point.s.x - start.x))
//			+ sin(p) * (t_point.s.y - start.y)));
//}

void	put_block(int i, int j, int color, t_img_d *img_d)
{
	int	k;
	int	l;

	k = i * mini_t;
	i = (i * mini_t) + mini_t;
	j *= mini_t;
	while (k < i)
	{
		l = j;
		while (l < j + mini_t)
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
	while (i < (img_d->height / mini_t))
	{
		j = 0;
		while (j < (img_d->width / mini_t))
		{
			put_block(i, j, get_value(0,
					255 * (gi->map[i][j] != '1'),
					255, 255 * (gi->map[i][j] != '1')), img_d);
			j++;
		}
		i++;
	}	
}

int	manage_keys(int k, t_data *all)
{
	int	new[2];
// flag 0 1
	new[0] = all->tp.s.x + (((k == w_key) * 14) + ((k == s_key) * -14)) * cos(all->nu.rot)
		+ (((k == a_key) * -14) + ((k == d_key) * 14)) * cos(all->nu.rot + M_PI_2);
	new[1] = all->tp.s.y + (((k == w_key) * 14) + ((k == s_key) * -14)) * sin(all->nu.rot)
		+ (((k == a_key) * -14) + ((k == d_key) * 14)) * sin(all->nu.rot + M_PI_2);
	if (all->img_d.p[new[0] + (new[1] * all->img_d.width)] == wall_c)
		return (-1);
	if (k == 3)
		all->nu.toggle = !all->nu.toggle;
	all->tp.s.x = new[0];
	all->tp.s.y = new[1];
	all->nu.rot += ((k == 124) * (M_PI / 65)) + ((k == 123) * (-M_PI / 65));
	all->nu.rot += (2 * M_PI) * (all->nu.rot < 0) + (-2 * M_PI) * (all->nu.rot > (2 * M_PI));
	return (0);
}


// keyup keydown

int	draw_sewindow(int x, double distance, int color, t_data *data)
{
	int	y;
	int	nu_pxls;
	int	di;

	distance += 1 * (!distance);
	if (data->nu.toggle)
		nu_pxls = data->nu.cons / distance;
	else
		nu_pxls = tile_s * main_h / distance;
	y = (main_h - nu_pxls) / 2;
	y = y * (y >= 0);
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
			put_pixel(x, y, &all->s.pic,
				all->nu.floar * (y > main_h / 2) + all->nu.sky * (y <= main_h / 2));
			x++;
		}
		y++;
	}
	return (0);
}

int	get_nearest(int x, int y, int x2, int y2)
{
	int	dx;
	int	dy;
	int	res;

	dx = x2 - x;
	dy = y2 - y;
	res = p_v(dx) - p_v(dy);
	res = (res > 0) + (2 * res <= 0);
	return (res * ((res == 1 * ((dx > 0) + -1
		* (dx < 1)) + res == 2 * ((dy > 0) + -1 * (dy < 1)))));
}

double	put_them(t_data *all, int *color, double angle)
{
	t_ps		p;
	double		distan[2];

	p.x = all->tp.s.x;
	p.y = all->tp.s.y;
	angle += (2 * M_PI) * (angle < 0) + (-2 * M_PI) * (angle > (2 * M_PI));
	t_ps *h = get_horizontal(p, all, angle);
	t_ps *v = get_vertical(p, all, angle);
	distan[0] = fabs((cos(all->nu.rot) * (p.x - h->x))
			+ sin(all->nu.rot) * (p.y - h->y));
	distan[1] = fabs((cos(all->nu.rot) * (p.x - v->x))
			+ sin(all->nu.rot) * (p.y - v->y));
	if (distan[0] <= distan[1])
	{
	//	draw_line(p.x, p.y, h->x, h->y, *color, all);
		*color = 255;
	}
	else
		*color = 4000;
	free(h);
	free(v);
	return (distan[0] * (distan[0] <= distan[1])
		+ distan[1] * (distan[1] < distan[0]));
}

int	draw_walls(t_data *all)
{
	double	distance;
	double	angle[2];
	int		x;
	int		color;

	x = 0;
	color = get_value(0, 0, 0, 255);
	angle[0] = all->nu.rot - (M_PI / 6);
	angle[1] = all->nu.rot + (M_PI / 6);
	while (angle[0] < angle[1])
	{
		distance = put_them(all, &color, angle[0]);
		draw_sewindow(x, distance, color, all);
		angle[0] += all->nu.inc_ray;
		x++;
	}
	return (0);
}

int	render_view(int key, t_data *all)
{
	if (manage_keys(key, all) == -1)
		return (-1);
	draw(&all->img_d, &all->inf);
	reset_img(all);
	draw_walls(all);
	mlx_put_image_to_window(all->inf.mlx,
		all->inf.window, all->img_d.img, 0, 0);
	mlx_put_image_to_window(all->inf.mlx,
		all->s.window, all->s.pic.img, 0, 0);
	return (1);
}

int	main(void)
{
	t_data	all_data;

	init_data(&all_data);
	initial_reading(&all_data, "map.cub");
//	render_view(-9, &all_data);
//	mlx_put_image_to_window(all_data.inf.mlx,
//		all_data.inf.window, all_data.img_d.img, 0, 0);
//	mlx_hook(all_data.s.window, 02, (1L << 0), render_view, &all_data);
//	mlx_put_image_to_window(all_data.inf.mlx,
//		all_data.s.window, all_data.s.pic.img, 0, 0);
//	mlx_loop(all_data.inf.mlx);
}
