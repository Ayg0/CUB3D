/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:28:40 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/10/28 10:00:31 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minilibx(t_data	*data)
{
	data->inf.mlx = mlx_init();
	data->inf.window = mlx_new_window(data->inf.mlx, data->img_d.width, data->img_d.height, "NICE");
	data->img_d.img = mlx_new_image(data->inf.mlx, data->img_d.width, data->img_d.height);
	data->img_d.p = (int *)mlx_get_data_addr(data->img_d.img, &data->img_d.b_by_p, &data->img_d.size_line, &data->img_d.endi);
	data->s.window = mlx_new_window(data->inf.mlx, main_w, main_h, "GAME WINDOW");
	data->s.pic.img = mlx_new_image(data->inf.mlx, main_w, main_h);
	data->s.pic.p = (int *)mlx_get_data_addr(data->s.pic.img, &data->s.pic.b_by_p, &data->s.pic.size_line, &data->s.pic.endi);	
}
void	init_nu(t_data *data)
{
	data->nu.cons = tile_s * (main_w / 2) / tan(M_PI / 6);
	data->nu.rot = 0;
	data->nu.sky = get_value(0, 0, 255, 191);
	data->nu.floar = get_value(0, 128, 128, 128);
	data->nu.inc_ray = (M_PI / 3) / main_w;
	data->s.pic.height = main_h;
	data->s.pic.width = main_w;
	data->nu.toggle = 0;
}

void	init_map(t_data *data)
{
	data->inf.map = read_map("./map", data->inf.max, data);
	data->img_d.height = data->inf.max[0] * mini_t;
	data->img_d.width = data->inf.max[1] * mini_t;
}

void	init_data(t_data *data)
{
	init_nu(data);
	init_map(data);
	init_minilibx(data);
}