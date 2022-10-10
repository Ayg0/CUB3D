#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>

typedef struct s_img_d
{
	int		*p;
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

typedef struct s_pic
{
	void	*p;
	void	*mpt;
	void	*wall;
} t_pic;

typedef struct s_info
{
	void	*window;
	void	*mlx;
	t_pic	pic;
	char	**map;
	int		max[2];
} t_info;

typedef	unsigned char u8bit;

int		ft_strlen(char	*s);
void	*ft_calloc(size_t count, size_t size);
char	*read_line(int fd);
#endif