/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:56:13 by smarty            #+#    #+#             */
/*   Updated: 2024/01/24 22:36:25 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_data *img)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(img->mlx_ptr, img->img);
		mlx_destroy_window(img->mlx_ptr, img->win_ptr);
		mlx_destroy_display(img->mlx_ptr);
		free (img->map);
		free(img->mlx_ptr);
		free (img);
		exit (EXIT_SUCCESS);
	}
	else if (keycode == 65360)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->mulx += 2;
		img->muly += 1;
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 65367)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		if (img->mulx > 2 && img->muly > 1)
		{
			img->mulx -= 2;
			img->muly -= 1;
		}
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 100)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->offsetx += 10;
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 113)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->offsetx -= 10;
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 122)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->offsety -= 10;
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 115)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->offsety += 10;
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 65365)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->mul += 1;
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 65366)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->mul -= 1;
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 121)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->corner_z = 0.05;
		apply_corner(img, 3, img->corner_z);
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 104)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->corner_z = -0.05;
		apply_corner(img, 3, img->corner_z);
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 117)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->corner_y = 0.05;
		apply_corner(img, 2, img->corner_y);
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 106)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->corner_y = -0.05;
		apply_corner(img, 2, img->corner_y);
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 105)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->corner_x = 0.05;
		apply_corner(img, 1, img->corner_x);
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 107)
	{
		recovery(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->corner_x = -0.05;
		apply_corner(img, 1, img->corner_x);
		draw_point(img);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	//else if (keycode == )
	printf("%d\n", keycode);
	return (0);
}
