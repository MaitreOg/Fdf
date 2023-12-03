/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:31:23 by smarty            #+#    #+#             */
/*   Updated: 2023/12/03 13:54:51 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	create_map(t_map **map, int fd)
{
	char	**line;
	int		x;
	int		y;
	t_map	*tmp;

	tmp = *map;
	y = 0;
	line = ft_split(get_next_line(fd), ' ');
	while(line)
	{
		x = 0;
		while (line[x])
		{
			tmp->x = x;
			tmp->y = y;
			tmp->z = ft_atoi(line[x]);
			x++;
			tmp = tmp->next;
		}
		y++;
		line = ft_split(get_next_line(fd), ' ');
	}
}

/*void draw_line(void *mlx_ptr, void *win_ptr, t_map **map)
{
	int px;
	int py;
	int pz;
	

}*/

void	create_win(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 900, "Fdf");
	mlx_loop(mlx_ptr);
	//draw_line(mlx_ptr,win_ptr);
}

int main()
{
	int		fd;
	t_map	*map;
	
	fd = open("42.fdf", 0);
	create_map(&map, fd);
	create_win();
}

//recupere la map
//affiche une fenetre
//afficher les lignes