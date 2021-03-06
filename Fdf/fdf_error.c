#include "fdf.h"


void		fdf_error(t_env *e)
{
	mlx_destroy_window(e->mlx_ptr, e->win_ptr);
	exit(0);
}

void		fdf_wrong_size_error(int flag)
{
	if (flag == 1)
		write(1, "Found wrong line length. Exiting.\n", 34);
	else if (flag == 2)
		write(1, "File is empty.\n", 16);
	exit(0);
}

void		fdf_malloc_fail(void)
{
	exit(0);
}