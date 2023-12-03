NAME	= fdf

LIBFT = libft/
GNL   = get_next_line/
MLX = minilibx_macos/

LIBFT_A = $(addprefix $(LIBFT), libft.a)
MLX_A   = $(addprefix $(GNL), libmlx.a)




CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = fdf.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT_A) $(LIBMLX_A)
	$(CC) $(CFLAGS) -o  $(OBJECTS) -L$(LIBFT) -lgnl -L$(MLX) -lmlx -lm -o $(NAME) framework OpenGL -framework AppKit

$(LIBFT_A): $(MAKE) -s -C $(LIBFT)

$(MLX_A): $(MAKE) -s -C $(MLX))

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re%