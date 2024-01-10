/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:31:23 by smarty            #+#    #+#             */
/*   Updated: 2024/01/10 16:58:59 by smarty           ###   ########.fr       */
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
	char **newline;
	char *line;
	int i;

	i = 0;
	tab = malloc(sizeof(char **) * (count_y() + 1));
	line = get_next_line(fd);
	while (line)
	{
		newline = ft_split(line, ' ');
		tab[i] = newline;
		free(line);
		i++;
		line = get_next_line(fd);
		
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
	//t_point	*tmp;
	char	***tab;
	int		x;
	int		y;
	int		i;
	
	y = 0;
	i = 0;
	tab = split_map(fd);
	i = len_map(tab);
	//tmp = malloc(sizeof(t_point));
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
	map->nbrline = y - 1;
	map->lenstruct = i - 1;
	return(tab);
}

/*void	recovery(t_data *map, int mul)
{
	int i;

	i = 0;
	while (i < map->len)
	{
		draw_line_y(map, i, 0xFF000000, mul);
		draw_line_x(map, i, 0xFF000000, mul);
		i++;
	}
}*/

void	free_tab(char ***tab)
{
	int i;
	int	y;

	i = 0;
	while(tab[i])
	{
		y = 0;
		while(tab[i][y])
		{
			free(tab[i][y]);
			y++;
		}
		free (tab[i]);
		i++;
	}
	free(tab);
}
void	create_win(int fd)
{
	char	***tab;
	t_data	*img;
	int		color;

	color = 0x00FFFFFF;
	img = malloc(sizeof(t_data));
	img->mul = 10;
	img->mlx_ptr = mlx_init();
	img->win_ptr = mlx_new_window(img->mlx_ptr, 900, 600, "Fdf");
	if (img->win_ptr == NULL)
	{
		exit(1);
	}
	img->img = mlx_new_image(img->mlx_ptr, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	tab = create_map(img, fd);
	img->len = len_map(tab);
	draw_point(img, img->mul, color);
	free_tab(tab);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img , 0, 0);
	mlx_key_hook(img->win_ptr, key_hook, img);
	mlx_loop(img->mlx_ptr);
	exit(0);
}


int main(void)
{
	int		fd;
	
	fd = open("test_maps/42.fdf", 0);
	create_win(fd);
	return (1);
}