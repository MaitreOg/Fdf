NAME	= fdf

LIBFT = libft/
MLX = minilibx-linux/

LIBFT_A = $(addprefix $(LIBFT), libft.a)
MLX_A   = $(addprefix $(MLX), libmlx.a)




CC = cc

CFLAGS = -Wall -Wextra -Werror -g

MLX_FLAGS = -L/usr/X11R6/lib -lX11 -lXext

SRCS = fdf.c  rotate.c draw.c key_hook.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_A) $(MLX_A) $(MLX_FLAGS) -o $(NAME)
$(LIBFT_A): 
	make -s -C $(LIBFT)
$(MLX_A): 
	make -s -C $(MLX)

clean:
	rm -f $(OBJECTS)
	make -s -C $(LIBFT) clean
	make -s -C $(MLX) clean

fclean: clean
	rm -f $(NAME)
	make -s -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re