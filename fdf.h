#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
//# include <X11/X.h>
//# include <X11/keysym.h>

typedef struct s_point{
	double	x;
	double	y;
	double	z;
}			t_point;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_point	*map;
}				t_data;

#endif