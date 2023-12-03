#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
//# include <X11/X.h>
//# include <X11/keysym.h>


typedef struct s_map{
	int 			x;
	int 			y;
	int             z;
	struct s_map   *next;

}					t_map;

#endif