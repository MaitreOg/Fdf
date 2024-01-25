#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

typedef struct s_point{
	double	x;
	double	y;
	double	z;
}			t_point;

typedef struct	s_data {
	void 	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		lenstruct;
	int		nbrline;
	int		endian;
	double		z_max;
	int		color_mode;
	int		mul;
	int 	mulx;
	int 	muly;
	double		corner_x;
	double		corner_y;
	double		corner_z;
	int		offsetx;
	int		offsety;
	int		len;
	t_point	*map;
	t_point	*coord_map;
}				t_data;

int	key_hook(int keycode, t_data *img);
void draw_point(t_data *map);
void	recovery(t_data *map);
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
void	apply_corner(t_data *map, int axe, double corner);

#ifdef __linux__
# include <X11/keysym.h>
# include <X11/X.h>
#elif __APPLE__
# include <ApplicationServices/ApplicationServices.h>
#endif

#endif