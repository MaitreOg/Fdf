/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:31:23 by smarty            #+#    #+#             */
/*   Updated: 2023/12/04 00:28:48 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int count_y(void)
{
	int		fd;
	char	c;
	int		count;

	count = 0;
	fd = open("test_maps/42.fdf", 0);
	while(read(fd, &c, 1))
	{
		if (c == '\n')
			count++;
	}
	close(fd);
	return (count);
}
char ***split_map(int fd)
{
	char ***tab;
	char **line;
	int i;

	i = 0;
	tab = malloc(sizeof(char **) * (count_y() + 1));
	line = ft_split(get_next_line(fd), ' ');
	while (line)
	{
		tab[i] = line;
		i++;
		line = ft_split(get_next_line(fd), ' ');
	}
	tab[i] = 0;
	return (tab);
}

int	len_map(char ***tab)
{
	int	i;
	int y;
	int	len;

	i = 0;
	len = 0;
	while(tab[i])
	{
		y = 0;
		while(tab[i][y])
		{
			len++;
			y++;
		}
		i++;
	}
	return (len);
}

char	***create_map(t_data *map, int fd)
{
	char	***tab;
	int		x;
	int		y;
	int		i;
	t_point	*tmp;

	
	y = 0;
	i = 0;
	tab = split_map(fd);
	i = len_map(tab);
	tmp = malloc(sizeof(t_point));
	map->map = malloc(sizeof(t_point) * i);
	i = 0;
	while(tab[y])
	{
		x = 0;
		while (tab[y][x])
		{
			map->map[i].x = x;
			map->map[i].y = y;
			map->map[i].z = ft_atoi(tab[y][x]);
			x++;
			i++;
		}
		y++;
	}
	return(tab);
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;
	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void draw_point(t_data *map, char ***tab)
{
	int i;
	int	len;
	int offset;

	i = 0;
	offset = 100;
	len = len_map(tab);
	while (i < len)
	{
		if (map->map[i].z == 0)
			ft_mlx_pixel_put(map, (map->map[i].x * 40 + map->map[i].y * 10 + offset), (map->map[i].y * 20 + offset - (map->map[i].z * 10)), 0x00AA00FF);
		else
			ft_mlx_pixel_put(map, (map->map[i].x * 40 + map->map[i].y * 10 + offset), (map->map[i].y * 20 + offset - (map->map[i].z * 10)), 0x0000FF55);
		i++;
	}
	

}



int	key_hook(int keycode, t_data *img)
{
	(void)img;
	printf("%d\n", keycode);
	return (0);
}
void	create_win(int fd)
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	***tab;
	t_data	*img;

	img = malloc(sizeof(t_data));
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 900, 600, "Fdf");
	img->img = mlx_new_image(mlx_ptr, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	/*y = -1;
	while (++y < 600)
	{
		x = -1;
		while (++x < 900)
		{
			ft_mlx_pixel_put(img, x, y, 0xFFFFFF);
			write(1, img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)), 1);
		}
	}*/
	//ft_mlx_pixel_put(img, 100, 100, 0xOORRGGBB);
	tab = create_map(img, fd);
	draw_point(img, tab);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img->img , 0, 0);
	mlx_key_hook(win_ptr, key_hook, img);
	mlx_loop(mlx_ptr);
	
}

int main()
{
	int		fd;
	
	fd = open("test_maps/42.fdf", 0);
	create_win(fd);
}