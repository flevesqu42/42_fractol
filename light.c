/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 02:17:57 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/29 01:54:46 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	light(t_gen *gen)
{
	if (!(gen->light.win = mlx_new_window(gen->mlx, X, Y
					, "Fract'ol - origin : light")))
		error(2);
	if (!(gen->light.img = mlx_new_image(gen->mlx, X, Y)))
		error(4);
	gen->light.tab = NULL;
	init_thread(&gen->light);
	clear(&gen->light);
	gen->light.f = &set_light;
	gen->light.mlx = gen->mlx;
	gen->light.data = mlx_get_data_addr(gen->light.img
			, &gen->light.bpp, &gen->light.size_line
			, &gen->light.endian);
	prev_f(&gen->light);
	mlx_hook(gen->light.win, 17, (1l << 0), exit_fct, &gen->light);
	mlx_hook(gen->light.win, 2, (1l << 0), key_function, &gen->light);
	mlx_hook(gen->light.win, 4, (1l << 13), button_function, &gen->light);
	mlx_hook(gen->light.win, 5, (1l << 13), release_fct, &gen->light);
	mlx_hook(gen->light.win, 6, (1l << 6), move_function, &gen->light);
}

int		light_bis(long double *zri, long double *cri, int i, t_fract *f)
{
	long double tmp[3];
	int			r;

	if (i < f->i_max && (tmp[1] = (zri[0] * zri[0]))
			+ (tmp[2] = (zri[1] * zri[1])) < 4)
	{
		tmp[0] = zri[0];
		zri[0] = (tmp[1] - tmp[2]) - zri[0] - cri[0];
		zri[1] = fabsl(2 * zri[1] * tmp[0]) - zri[1] - cri[1];
		tmp[0] = ((zri[0] - -1.92 - (f->x + f->fx)))
			* (double)((f->zoom * f->hd) / 2.4);
		tmp[1] = (zri[1] - -1.2 - (f->y + f->fy))
			* (double)((f->zoom * f->hd) / 2.4);
		if ((r = light_bis(zri, cri, i + 1, f))
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

void	*set_light(void *d)
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
		while (++xy[0] < xy[3] * m.hd)
		{
			cri[0] = m.jx;
			cri[1] = m.jy;
			zri[0] = (xy[0] / add[2] + -1.92 + add[0]);
			zri[1] = xy[1] / add[2] + -1.2 + add[1];
			light_bis(zri, cri, 0, &m);
		}
	return (NULL);
}
