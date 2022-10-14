#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>

# define w_key 13
# define s_key 1
# define a_key 0
# define d_key 2
# define main_h 720
# define main_w 1280

typedef struct s_img_d
{
	int		*p;
	void	*img;
	int		b_by_p;
	int		size_line;
	int		endi;
	int		height;
	int		width;
} t_img_d;

typedef	struct s_ps
{
	int	x;
	int	y;
} t_ps;

typedef	struct s_tp
{
	t_ps	s;
	t_ps	e;
} t_tp;


typedef struct s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
} t_color;

typedef struct s_info
{
	void	*window;
	void	*mlx;
	char	**map;
	int		max[2];
} t_info;

typedef struct s_s_win
{
	void	*window;
	t_img_d	pic;
} t_s_win;

typedef struct s_all_data
{
	t_info	inf;
	t_tp	tp;
	float	rot;
	t_s_win	s;
	t_img_d	img_d;
} t_data;

typedef	unsigned char u8bit;

int		ft_strlen(char	*s);
void	*ft_calloc(size_t count, size_t size);
char	*read_line(int fd);
char	**read_map(char	*map_name, int	*max);
#endif