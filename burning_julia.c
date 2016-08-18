/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 21:18:27 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/28 04:16:02 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	bjulia(t_gen *gen)
{
	if (!(gen->bjulia.win = mlx_new_window(gen->mlx, X, Y
					, "Fract'ol - origin : burning_julia")))
		error(2);
	if (!(gen->bjulia.img = mlx_new_image(gen->mlx, X, Y)))
		error(4);
	init_thread(&gen->bjulia);
	clear(&gen->bjulia);
	gen->bjulia.rep = 0;
	gen->bjulia.r = 0x00;
	gen->bjulia.v = 0x50;
	gen->bjulia.b = 0x05;
	gen->bjulia.tab = NULL;
	gen->bjulia.f = &set_bjulia;
	gen->bjulia.mlx = gen->mlx;
	gen->bjulia.data = mlx_get_data_addr(gen->bjulia.img
			, &gen->bjulia.bpp, &gen->bjulia.size_line
			, &gen->bjulia.endian);
	prev_f(&gen->bjulia);
	mlx_hook(gen->bjulia.win, 17, (1l << 0), exit_fct, &gen->bjulia);
	mlx_hook(gen->bjulia.win, 2, (1l << 0), key_function, &gen->bjulia);
	mlx_hook(gen->bjulia.win, 4, (1l << 13), button_function, &gen->bjulia);
	mlx_hook(gen->bjulia.win, 5, (1l << 13), release_fct, &gen->bjulia);
	mlx_hook(gen->bjulia.win, 6, (1l << 6), move_function, &gen->bjulia);
}

void	bjulia_bis(long double *zri, long double *cri, int *xy, t_fract *f)
{
	long double tmp[3];
	int			col;
	int			i;

	col = ((0x000001 * f->b) + (0x000100 * f->v) + (0x010000 * f->r));
	i = 0;
	while (i < f->i_max && (tmp[1] = (zri[0] * zri[0]))
			+ (tmp[2] = (zri[1] * zri[1])) < 8)
	{
		tmp[0] = zri[0];
		zri[0] = (tmp[1] - tmp[2]) + cri[0];
		zri[1] = fabsl(2 * zri[1] * tmp[0]) + cri[1];
		++i;
	}
	if (i < f->i_max || (f->rep & 0x10))
	{
		i = f->rep & 0x100 ? f->i_max - i : i;
		img_pixel_put(f, xy[0], xy[1], f->rep & 0x4 ? color(i, f) : i * col);
	}
}

void	*set_bjulia(void *d)
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
		while (++xy[0] < xy[3] && !(zri[0] = 0)
			&& !(zri[1] = 0))
		{
			cri[0] = m.jx;
			cri[1] = m.jy;
			zri[0] = (xy[0] / add[2] + -1.92 + add[0]);
			zri[1] = xy[1] / add[2] + -1.2 + add[1];
			bjulia_bis(zri, cri, xy, &m);
		}
	return (NULL);
}
