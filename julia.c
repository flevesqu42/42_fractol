/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 08:54:25 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/28 07:41:09 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_gen *gen)
{
	if (!(gen->julia.win = mlx_new_window(gen->mlx, X, Y
					, "Fract'ol - origin: julia")))
		error(2);
	if (!(gen->julia.img = mlx_new_image(gen->mlx, X, Y)))
		error(4);
	init_thread(&gen->julia);
	clear(&gen->julia);
	gen->julia.rep = 0;
	gen->julia.r = 0x00;
	gen->julia.v = 0x50;
	gen->julia.b = 0x05;
	gen->julia.tab = NULL;
	gen->julia.f = &set_julia;
	gen->julia.mlx = gen->mlx;
	gen->julia.data = mlx_get_data_addr(gen->julia.img
			, &gen->julia.bpp, &gen->julia.size_line
			, &gen->julia.endian);
	prev_f(&gen->julia);
	mlx_hook(gen->julia.win, 17, (1l << 0), exit_fct, &gen->julia);
	mlx_hook(gen->julia.win, 2, (1l << 0), key_function, &gen->julia);
	mlx_hook(gen->julia.win, 4, (1l << 13), button_function, &gen->julia);
	mlx_hook(gen->julia.win, 5, (1l << 13), release_fct, &gen->julia);
	mlx_hook(gen->julia.win, 6, (1l << 6), move_function, &gen->julia);
}

int		move_function(int x, int y, t_fract *f)
{
	long double	fx;
	long double	fy;

	if (x < 0 || y < 0 || x >= X || y >= Y)
		return (0);
	fx = (long double)x;
	fy = (long double)y;
	if (f->rep & 0x2)
	{
		f->fx = (f->sx - fx) / (f->zoom / (2.4));
		f->fy = (f->sy - fy) / (f->zoom / (2.4));
		mlx_clear_window(f->mlx, f->win);
		prev_f(f);
	}
	else if (!(f->rep & 0x3) && (f->f == &set_julia || f->f == &set_bjulia
	|| f->f == &set_jghost || f->f == &set_light))
	{
		f->jx = fx / (f->zoom / (2.4)) + -2.1 + f->x;
		f->jy = fy / (f->zoom / (2.4)) + -1.2 + f->y;
		mlx_clear_window(f->mlx, f->win);
		prev_f(f);
	}
	return (0);
}

void	julia_bis(long double *zri, long double *cri, int *xy, t_fract *f)
{
	long double tmp[3];
	int			col;
	int			i;

	col = ((0x000001 * f->b) + (0x000100 * f->v) + (0x010000 * f->r));
	i = 0;
	while (i < f->i_max && (tmp[1] = (zri[0] * zri[0]))
			+ (tmp[2] = (zri[1] * zri[1])) < 4)
	{
		tmp[0] = zri[0];
		zri[0] = tmp[1] - tmp[2] + cri[0];
		zri[1] = (2 * zri[1] * tmp[0]) + cri[1];
		++i;
	}
	if (i < f->i_max || (f->rep & 0x10))
	{
		i = f->rep & 0x100 ? f->i_max - i : i;
		img_pixel_put(f, xy[0], xy[1], f->rep & 0x4 ? color(i, f) : i * col);
	}
}

void	*set_julia(void *d)
{
	int			xy[4];
	long double	cri[2];
	long double	zri[2];
	long double	add[3];
	t_fract		m;

	m = *((t_thread*)d)->m;
	xy[2] = ((t_thread*)d)->lim[0];
	xy[3] = ((t_thread*)d)->lim[1];
	xy[1] = -1;
	add[0] = m.x + m.fx;
	add[1] = m.y + m.fy;
	add[2] = (double)m.zoom / (2.4);
	while (++xy[1] < Y && (xy[0] = xy[2] - 1))
		while (++xy[0] < xy[3])
		{
			cri[0] = m.jx;
			cri[1] = m.jy;
			zri[0] = xy[0] / add[2] + -1.92 + add[0];
			zri[1] = xy[1] / add[2] + -1.2 + add[1];
			julia_bis(zri, cri, xy, &m);
		}
	return (NULL);
}
