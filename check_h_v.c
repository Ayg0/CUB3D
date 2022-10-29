/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_h_v.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 08:56:26 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/10/27 16:53:02 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	not_wall(t_ps ray, t_data *data)
{
	int	grid[2];

	grid[0] = (int)ray.x / mini_t;
	grid[1] = (int)ray.y / mini_t;
	return (grid[0] > 0 && grid[1] > 0 && grid[0] < data->inf.max[1]
		&& grid[1] < data->inf.max[0] && data->inf.map[grid[1]][grid[0]] != '1');
	//return (ray.x >= 0 && ray.y >= 0 && ray.x < data->img_d.width
	//	&& ray.y < data->img_d.height && data->img_d.p[(int)ray.x + ((int)ray.y * data->img_d.width)] != wall_c);
}

void draw_line(int x0, int y0, int x1, int y1, int color, t_data *data)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
    int e2;

    while (1)
    {
		if (!put(x0, y0, &data->img_d, color))
			return ;
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * error;
        if (e2 >= dy)
        {
            if (x0 == x1)
                break;
            error = error + dy;
            x0 = x0 + sx;
        }
        if (e2 <= dx)
        {
            if (y0 == y1)
                break;
            error = error + dx;
            y0 = y0 + sy;
        }
    }
}

t_ps	*get_vertical(t_ps p, t_data *data, double angle)
{
	t_ps	*ray = malloc(sizeof(t_ps));
	double	t;
	double	x_step;
	double	y_step;
	int		dof;

	t = -tan(angle);
	dof = 0;
	printf("%f\n", angle);
	if (angle < 3 * M_PI / 2 && angle > M_PI / 2) // looking right
	{
		ray->x = ((int)p.x / mini_t) * mini_t - 0.0001;
		ray->y = (p.x - ray->x) * t + p.y;
		x_step = -mini_t;
		y_step = -x_step * t; 
	}
	if (angle > 3 * M_PI / 2 || angle < M_PI / 2) // looking left
	{
		ray->x = ((int)p.x / mini_t) * mini_t + mini_t;
		ray->y = (p.x - ray->x) * t + p.y;
		x_step = mini_t;
		y_step = -x_step * t;
	}
	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
	{
		ray->x = p.x + 5000;
		ray->y = p.y + 5000;
		dof = max_dof;
	}
	while (dof < max_dof && not_wall(*ray, data))
	{
		ray->x += x_step;
		ray->y += y_step;
		dof++;
	}
	return (ray);
}

t_ps	*get_horizontal(t_ps p, t_data *data, double angle)
{
	t_ps	*ray = malloc(1 * sizeof(t_tp));
	double	t;
	double	x_step;
	double	y_step;
	int		dof;

	dof = 0;
	t = -tan(angle);
	printf("%f\n", angle);
	if (angle > M_PI) // looking up
	{
		ray->y = ((int)p.y / mini_t) * mini_t - 0.0001;
		ray->x = ((p.y - ray->y) / t) + p.x;
		y_step = -mini_t;
		x_step = -y_step / t; 
	}
	if (angle < M_PI) // looking down
	{
		ray->y = ((int)p.y / mini_t) * mini_t + mini_t;
		ray->x = ((p.y - ray->y) / t) + p.x;
		y_step = mini_t;
		x_step = -y_step / t;
	}
	if (angle == M_PI || !angle)
	{
		ray->x = p.x + 5000;
		ray->y = p.y + 5000;
		dof = max_dof;
	}
	while (dof < max_dof && not_wall(*ray, data))
	{
		ray->x += x_step;
		ray->y += y_step;
		dof++;
	}
	return (ray);
}