/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dx_dy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:50:05 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/10/23 14:54:55 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_dx_dy(int *dxy, t_tp t_point, t_img_d *img_d, int color)
{
	int		d[2];
	t_ps	start;

	d[0] = t_point.e.x - t_point.s.x;
	d[1] = t_point.e.y - t_point.s.y;
	start.x = t_point.s.x;
	start.y = t_point.s.y;
	(p_v(d[0]) > p_v(d[1])) && draw_case1(&t_point, d, img_d, color);
	(p_v(d[0]) <= p_v(d[1])) && draw_case2(&t_point, d, img_d, color);
	dxy[0] = t_point.s.x - start.x;
	dxy[1] = t_point.s.y - start.y;
}