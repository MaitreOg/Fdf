/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:53:12 by smarty            #+#    #+#             */
/*   Updated: 2024/01/10 18:06:27 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;
	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}
int	test_coord(int x, int y)
{
	if (x < 0 || y < 0 || x > 1920 || y > 1080)
		return (1);
	return (0);
}

void	draw_line_x(t_data *map, int y, int color , int mul)
{
	float	vx;
	float	vy;
	float	cd;
	int		i;
	int		z;
	int 	sign;


	i = -1;
	vx = map->map[y].x * 40 + 100;
	vy = map->map[y].y * 20 + 100 - map->map[y].z * mul;
	if (map->map[y + 1].x > map->map[y].x)
	{
		cd = fabs((map->map[y + 1].z - map->map[y].z) / (40 / mul));
		sign = (((map->map[y + 1].z - map->map[y].z) / (40 / mul)) / cd) * -1;
		while (i++ < 40)
		{
			z = (i - 1) * cd;
			if (z < 0)
				z = 0;
			while (z < (i * cd)) 
			{
				ft_mlx_pixel_put(map, vx + i + (map->map[y].y * 10), vy + (z * sign), color);
				z++;
			}
			ft_mlx_pixel_put(map, vx + i + (map->map[y].y * 10), vy + (z * sign), color);
		}
	}
}


int	len_line(t_data *map, int i, double y, double x)
{
	while (map->map[i].y == y)
		i++;
	while (map->map[i].y == (y + 1))
	{
		if (map->map[i].x == x)
		{
			//printf("%f\n",map->map[i].y);
			return (i);
		}
		i++;
	}
	return (0);
}

void	draw_line_y(t_data *map, int i, int color, int mul)
{
	
	int		len;
	int		vx;
	int		vy;
	float	cd;
	float	y;
	
	vx = map->map[i].x * 40 + 100;
	vy = map->map[i].y * 20 + 100;
	y = -1;
	cd = 0;
	if (map->map[i].y < map->nbrline)
	{
		len = len_line(map, i, map->map[i].y, map->map[i].x);
		if (map->map[len].z != map->map[i].z)
			cd = -1 * ((map->map[len].z - map->map[i].z) / (20 / mul));
		if (cd > 1 || cd < -1)
		{	
			while(fabsf(++y / cd) < 20)
			{
				if (test_coord((vx + map->map[i].y * 10) + (y / fabsf(2 * cd)) , vy - map->map[i].z * mul + (y * (cd / fabsf(cd))) + (fabsf(y / (cd)))) == 0)
					ft_mlx_pixel_put(map, (vx + map->map[i].y * 10) + (y / fabsf(2 * cd)) , vy - map->map[i].z * mul + (y * (cd / fabsf(cd))) + (fabsf(y / (cd))), color);
			}
		}
		else
		{
			if (test_coord((vx + map->map[i].y * 10) + (y / 2), vy + (y * cd) - map->map[i].z * mul + y) == 0)
			{
				while (++y < 20)
					ft_mlx_pixel_put(map, (vx + map->map[i].y * 10) + (y / 2) , vy + (y * cd) - map->map[i].z * mul + y, color);
			}
		}
	}
}

void	draw_line(t_data *map, t_point a, t_point b)
{
	t_point	vector;
	double	cd;
	int		i;

	i = 0;
	cd = (b.y - a.y) / (b.y - a.y);
	while (i < 40)
	{
		vector.x = a.x + i + 100;
		vector.y = a.y + ((i * cd) / 1) + 100;
		ft_mlx_pixel_put(map, vector.x, vector.y, 0x0000FF00);
		i++;
	}
}

void	draw_point(t_data *map, int mul, int color)
{
	int i;
	int offset;

	i = 0;
	offset = 100;
	while (i < map->len)
	{
		//if (map->map[i].z == 0)
		//	ft_mlx_pixel_put(map, (map->map[i].x * 40 + map->map[i].y * 10 + offset), (map->map[i].y * 20 + offset - (map->map[i].z * 10)), 0x00AA00FF);
		//else
		//ft_mlx_pixel_put(map, (map->map[i].x * 40 + map->map[i].y * 10 + offset), (map->map[i].y * 20 + offset - (map->map[i].z * 10)), 0x0000FF55);
		if (map->map[i].z == 0 && map->map[i + 1].z == 0)
		{
			draw_line(map, map->map[i], map->map[i + 1]);
			draw_line_y(map, i, color, mul);
		}
		else if (map->map[i].z  - map->map[i + 1].z == map->map[i].z || map->map[i + 1].z  - map->map[i].z == map->map[i + 1].z)
		{
			draw_line_y(map, i, color, mul);
			draw_line_x(map, i, color, mul);
		}
		else if (map->map[i].z  - map->map[i + 1].z == 0)
		{
			draw_line_y(map, i, color, mul);
			draw_line_x(map, i, color, mul);
		}
		i++;
	}
}