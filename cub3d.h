#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>

# define w_key		13
# define s_key		1
# define a_key		0
# define d_key		2
# define main_h		1020
# define main_w		1800
# define wall_c		255
# define tile_s		32
# define mini_t		32
# define h_line		9437258
# define v_line		1729620
# define max_dof	800

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
	double	x;
	double	y;
} t_ps;

typedef	struct s_tp
{
	t_ps	s;
	t_ps	e;
} t_tp;

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

typedef	struct s_nums
{
	double	rot;
	double	cons;
	int		sky;
	int		floar;
	double	inc_ray;
	int		toggle;
}	t_nums;

typedef	struct s_tmp
{
	char			*tmp;
	struct s_tmp	*next;
}t_tmp;

typedef	struct s_config
{
	char	*names[7];
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		fc;
	int		cc;
	int		w_h[2];
	char	**map;
}	t_config;

typedef struct s_all_data
{
	t_info		inf;
	t_tp		tp;
	t_s_win		s;
	t_nums		nu;
	t_img_d		img_d;
	t_tmp		*parts;
	t_config	config;
} t_data;



typedef	unsigned char u8bit;

// general:
int		ft_strlen(char	*s);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
// load_map:
char	*read_line(int fd);
char	**read_map(char	*map_name, int	*max, t_data *data);
// init_data:
void	init_data(t_data *data);
int		get_value(u8bit tr, u8bit red, u8bit blue, u8bit green);
//draw:
void	get_dx_dy(int *dxy, t_tp t_point, t_img_d *img_d, int color);
int		draw_case2(t_tp *new, int *d, t_img_d *img_d, int color);
int		draw_case1(t_tp *new, int *d, t_img_d *img_d, int color);
int		put(int x, int y, t_img_d *img_d, int color);
t_ps h_intersection(t_data *data, int player_x, int player_y, double radian);
t_ps v_intersection(t_data *data, int player_x, int player_y, double radian);
void draw_line(int x0, int y0, int x1, int y1, int color, t_data *data);
//double	draw_line(t_tp t_point, t_img_d *img_d, int color, double p);
int		p_v(int value);
double	p_vf(double value);
// horizontal and vertical inter:
t_ps	*get_horizontal(t_ps p, t_data *data, double angle);
t_ps	*get_vertical(t_ps p, t_data *data, double angle);
#endif