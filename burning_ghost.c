/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ghost.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 09:06:32 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/29 01:49:47 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ghost(t_gen *gen)
{
	if (!(gen->ghost.win = mlx_new_window(gen->mlx, X, Y
					, "Fract'ol - origin : burning_ghost")))
		error(2);
	if (!(gen->ghost.img = mlx_new_image(gen->mlx, X, Y)))
		error(4);
	gen->ghost.tab = NULL;
	init_thread(&gen->ghost);
	clear(&gen->ghost);
	gen->ghost.f = &set_ghost;
	gen->ghost.mlx = gen->mlx;
	gen->ghost.data = mlx_get_data_addr(gen->ghost.img
			, &gen->ghost.bpp, &gen->ghost.size_line
			, &gen->ghost.endian);
	prev_f(&gen->ghost);
	mlx_hook(gen->ghost.win, 17, (1l << 0), exit_fct, &gen->ghost);
	mlx_hook(gen->ghost.win, 2, (1l << 0), key_function, &gen->ghost);
	mlx_hook(gen->ghost.win, 4, (1l << 13), button_function, &gen->ghost);
	mlx_hook(gen->ghost.win, 5, (1l << 13), release_fct, &gen->ghost);
	mlx_hook(gen->ghost.win, 6, (1l << 6), move_function, &gen->ghost);
}

int		ghost_bis(long double *zri, long double *cri, int i, t_fract *f)
{
	long double tmp[3];
	int			r;

	if (i < f->i_max && (tmp[1] = (zri[0] * zri[0]))
			+ (tmp[2] = (zri[1] * zri[1])) < 4)
	{
		tmp[0] = zri[0];
		zri[0] = tmp[1] - tmp[2] + cri[0];
		zri[1] = fabsl(2 * zri[1] * tmp[0]) + cri[1];
		tmp[0] = ((zri[0] - -2.0 - (f->x + f->fx)))
			* (double)((f->zoom * f->hd) / 2.4);
		tmp[1] = (zri[1] - -1.3 - (f->y + f->fy))
			* (double)((f->zoom * f->hd) / 2.4);
		if ((r = ghost_bis(zri, cri, i + 1, f))
				&& tmp[0] > 0 && tmp[0] < X * f->hd && tmp[1] > 0
				&& tmp[1] < Y * f->hd)
			++f->tab[(int)tmp[1] / f->hd][(int)tmp[0] / f->hd];
		return (r);
	}
	if ((i < f->i_max && !(f->rep & 0x200))
			|| (f->rep & 0x200 && i == f->i_max))
		return (1);
	else
		return (0);
}

void	*set_ghost(void *d)
{
	int			xy[4];
	long double	cri[2];
	long double	zri[2];
	long double	add[3];
	t_fract		m;

	m = *((t_thread*)d)->m;
	xy[2] = ((t_thread*)d)->lim[0];
	xy[3] = ((t_thread*)d)->lim[1];
	add[0] = m.x + m.fx;
	add[1] = m.y + m.fy;
	add[2] = (m.zoom * m.hd) / (2.4);
	xy[1] = -1;
	while (++xy[1] < Y * m.hd && (xy[0] = (xy[2] * m.hd) - 1))
		while (++xy[0] < (xy[3] * m.hd) && !(zri[0] = 0)
			&& !(zri[1] = 0))
		{
			cri[0] = (xy[0] / add[2] + -2.0 + add[0]);
			cri[1] = xy[1] / add[2] + -1.3 + add[1];
			ghost_bis(zri, cri, 0, &m);
		}
	return (NULL);
}
