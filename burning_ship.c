/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 03:27:50 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/28 04:11:18 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	burning_ship(t_gen *gen)
{
	if (!(gen->burn.win = mlx_new_window(gen->mlx, X, Y
					, "Fract'ol - origin : burning_ship")))
		error(2);
	if (!(gen->burn.img = mlx_new_image(gen->mlx, X, Y)))
		error(4);
	init_thread(&gen->burn);
	clear(&gen->burn);
	gen->burn.rep = 0;
	gen->burn.r = 0x00;
	gen->burn.v = 0x50;
	gen->burn.b = 0x05;
	gen->burn.f = &set_burn;
	gen->burn.mlx = gen->mlx;
	gen->burn.data = mlx_get_data_addr(gen->burn.img
			, &gen->burn.bpp, &gen->burn.size_line
			, &gen->burn.endian);
	prev_f(&gen->burn);
	mlx_hook(gen->burn.win, 17, (1l << 0), exit_fct, &gen->burn);
	mlx_hook(gen->burn.win, 2, (1l << 0), key_function, &gen->burn);
	mlx_hook(gen->burn.win, 4, (1l << 13), button_function, &gen->burn);
	mlx_hook(gen->burn.win, 5, (1l << 13), release_fct, &gen->burn);
	mlx_hook(gen->burn.win, 6, (1l << 6), move_function, &gen->burn);
}

void	burn_bis(long double *zri, long double *cri, int *xy, t_fract *f)
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
		zri[1] = fabsl(2 * zri[1] * tmp[0]) + cri[1];
		++i;
	}
	if (i < f->i_max || (f->rep & 0x10))
	{
		i = f->rep & 0x100 ? f->i_max - i : i;
		img_pixel_put(f, xy[0], xy[1], f->rep & 0x4 ? color(i, f) : i * col);
	}
}

void	*set_burn(void *d)
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
	add[2] = m.zoom / (2.4);
	while (++xy[1] < Y && (xy[0] = xy[2] - 1))
		while (++xy[0] < xy[3] && !(zri[0] = 0)
			&& !(zri[1] = 0))
		{
			cri[0] = -(xy[0] / add[2] + -1.5 + add[0]);
			cri[1] = (xy[1] / add[2] + -1.8 + add[1]);
			burn_bis(zri, cri, xy, &m);
		}
	return (NULL);
}
