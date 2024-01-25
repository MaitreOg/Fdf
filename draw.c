/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:53:12 by smarty            #+#    #+#             */
/*   Updated: 2024/01/24 22:31:36 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	test_coord(int x, int y)
{
	if (x < 0 || y < 0 || x > 1920 || y > 1080)
		return (1);
	return (0);
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (test_coord(x, y) == 0)
	{
		char	*dest;
		dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

int	len_line(t_data *map, int i, double y, double x)
{
	while (map->coord_map[i].y == y)
		i++;
	while (map->coord_map[i].y == (y + 1))
	{
		if (map->coord_map[i].x == x)
		{
			//printf("%f\n",map->map[i].y);
			return (i);
		}
		i++;
	}
	return (0);
}
int set_color2(double z, t_data *map)
{
	double	value;

	value = fabs(map->z_max * map->mul);
	if (z < -(value / 5) * 4)
		return (0x00A700FF); 
	if (z >= -(value / 5) * 4 && z < -(value / 5) * 3)
		return (0x006F00FF);
	if (z >= -(value / 5) * 3 && z < -(value / 5) * 2)
		return (0x000000FF);
	if (z >= -(value / 5) * 2 && z < -(value / 5))
		return (0x000066FF);
	if (z >= -(value / 5) && z < 0)
		return (0x0000CCFF);  
	if (z == 0)
		return (0x0000FF00);
	if (z > 0 && z <= (value / 5))
		return (0x0099FF66);
	if (z > (value / 5) && z <= (value / 5) * 2)
		return (0x00FFFF00);
	if (z > (value / 5) * 2 && z <= (value / 5) * 3)
		return (0x00FFCC00);
	if (z > (value / 5) * 3 && z <= (value / 5) * 4)
		return (0x00FF6600);
	if (z > (value / 5) * 4)
		return (0x00FF0000);
	return (0);
}

int	set_color3(double z, t_data *map)
{
	/*int	color;
	int	blue;
	int	green;
	int	red;

	color = 0x00;
	green = FF;
	if  (z > 0)
	{
		blue = 00;
		red = FF * (map->z_max * map->mul / z);
		green -= red;
	}
	if  (z < 0)
	{
		red = 00;
		blue = FF * -(map->z_max * map->mul / z);
		green -= blue;
	}
	return(color + red + green + blue);
	*/
	map->z_max = z;
	z = map->z_max;
	return (0x00FFFFFF);
}

int set_color(double bz, double az, int i, double cd, t_data *map)
{
	if (az == bz && map->color_mode == 0)
		return (set_color2(az, map));
	else if (fabs(az) / fabs(bz) < 1 && map->color_mode == 0)
		return (set_color2((az + (bz - az) * i) / cd, map));
	else if (map->color_mode == 0)
		return (set_color2((bz + (az - bz) * (cd - i)) / cd, map));
	if (az == bz && map->color_mode == 1)
		return (set_color3(az, map));
	else if (fabs(az) / fabs(bz) < 1 && map->color_mode == 1)
		return (set_color3((az + (bz - az) * i) / cd, map));
	else
		return (set_color3((bz + (az - bz) * (cd - i)) / cd, map));
}

void	draw_line(t_data *map, t_point a, t_point b, t_point color_a, t_point color_b)
{
	t_point	vector;
	t_point	pix;
	double	cd;
	//double	dimension;
	int		i;

	i = 0;
	a.x *= map->mulx;
	a.y *= map->muly;
	a.z *= map->mul;
	b.x *= map->mulx;
	b.y *= map->muly;
	b.z *= map->mul;

	vector.x = (b.x - a.x);
	vector.y = (b.y - a.y) - (b.z - a.z);
	cd = fabs(vector.x) + fabs(vector.y);
	a.x += map->offsetx;
	a.y += map->offsety;
	b.y += map->offsety;
	b.x += map->offsetx;
	while (i < cd)
	{
		//dimension = (a.y - 100) / (20 / 8) + (b.y - a.y) * (i / (cd * (20 / 8)));
		pix.x = a.x + (vector.x * i) / cd;// + dimension;
		pix.y = (a.y - a.z) + (vector.y * i) / cd;
		ft_mlx_pixel_put(map, pix.x , pix.y, set_color(color_b.z * map->mul,  color_a.z * map->mul, i ,cd, map));
		i++;
	}
}

void	draw_point(t_data *map)
{
	int i;
	int len;

	i = 0;
	while (i < map->len)
	{
		len = len_line(map, i, map->coord_map[i].y, map->coord_map[i].x);
		if (map->coord_map[i + 1].x > map->coord_map[i].x)
			draw_line(map, map->map[i], map->map[i + 1], map->coord_map[i], map->coord_map[i + 1]);
		if (map->coord_map[len].y > map->coord_map[i].y)
			draw_line(map, map->map[i], map->map[len],  map->coord_map[i], map->coord_map[len]);
		i++;
	}
}
