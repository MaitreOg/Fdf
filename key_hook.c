/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:56:13 by smarty            #+#    #+#             */
/*   Updated: 2024/01/10 16:56:58 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_data *img)
{
	int	i;

	i = 0;
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
	else if (keycode == 65362)
	{
		draw_point(img, img->mul, 0x00000000);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->mul += 1;
		draw_point(img, img->mul, 0x00FFFFFF);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	else if (keycode == 65364)
	{
		draw_point(img, img->mul, 0x00000000);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
		img->mul -= 1;
		draw_point(img, img->mul, 0x00FFFFFF);
		mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	}
	//else if (keycode == )
	printf("%d\n", keycode);
	return (0);
}