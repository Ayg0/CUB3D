#include "cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

	i = (!s * -1);
	while (s && s[i])
		i++;
	return (i);
}

int	get_value(u8bit tr, u8bit red, u8bit blue, u8bit green)
{
	return (tr << 24 | red << 16 | green << 8 | blue);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*p;
	size_t	i;

	total = size * count;
	p = (char *)malloc(total);
	if (!p)
		exit(write(2,"Error Allocation failed !\n", 26));
	i = -1;
	while (++i < total)
		p[i] = 0;
	return ((void *)p);
}