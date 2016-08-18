/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 03:27:50 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/29 01:54:49 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	buddha(t_gen *gen)
{
	if (!(gen->buddha.win = mlx_new_window(gen->mlx, X, Y
					, "Fract'ol - origin : buddhabrot")))
		error(2);
	if (!(gen->buddha.img = mlx_new_image(gen->mlx, X, Y)))
		error(4);
	gen->buddha.tab = NULL;
	init_thread(&gen->buddha);
	clear(&gen->buddha);
	gen->buddha.f = &set_buddha;
	gen->buddha.mlx = gen->mlx;
	gen->buddha.data = mlx_get_data_addr(gen->buddha.img
			, &gen->buddha.bpp, &gen->buddha.size_line
			, &gen->buddha.endian);
	prev_f(&gen->buddha);
	mlx_hook(gen->buddha.win, 17, (1l << 0), exit_fct, &gen->buddha);
	mlx_hook(gen->buddha.win, 2, (1l << 0), key_function, &gen->buddha);
	mlx_hook(gen->buddha.win, 4, (1l << 13), button_function, &gen->buddha);
	mlx_hook(gen->buddha.win, 5, (1l << 13), release_fct, &gen->buddha);
	mlx_hook(gen->buddha.win, 6, (1l << 6), move_function, &gen->buddha);
}

void	clear_buddha(t_fract *f)
{
	int	i;

	if (!(f->rep & 0x4))
		f->rep ^= 0x4;
	if (!f->tab)
	{
		f->hd = 1;
		f->c = 0x00;
		f->r = 0x30;
		f->v = 0xff;
		f->b = 0xff;
		f->i_max = 100;
		i = -1;
		if (!(f->tab = (int**)malloc(sizeof(int*) * Y)))
			error(3);
		while (++i < Y)
			if (!(f->tab[i] = (int*)ft_memalloc(sizeof(int) * X)))
				error(3);
	}
}

void	prev_buddha(t_fract *f)
{
	pthread_t	t[MT];
	int			y;
	int			i;

	clear_buddha(f);
	y = -1;
	while (++y < Y && (i = -1))
		while (++i < X)
			f->tab[y][i] = 0;
	y = -1;
	while (++y < MT)
		pthread_create(&t[y], NULL, f->f, &f->m[y]);
	i = -1;
	while (++i < MT)
		pthread_join(t[i], NULL);
	y = -1;
	while (++y < Y && (i = -1))
		while (++i < X)
			if (f->tab[y][i])
				img_pixel_put(f, i, y
					, color((double)f->tab[y][i]
					* ((double)f->i_max / (10 * (f->hd * f->hd))), f));
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	ft_bzero(f->data, f->size_line * Y);
}

int		buddha_bis(long double *zri, long double *cri, int i, t_fract *f)
{
	long double	tmp[3];
	int			r;

	if (i < f->i_max && (tmp[1] = (zri[0] * zri[0]))
			+ (tmp[2] = (zri[1] * zri[1])) < 4)
	{
		tmp[0] = zri[0];
		zri[0] = tmp[1] - tmp[2] + cri[0];
		zri[1] = (2 * zri[1] * tmp[0]) + cri[1];
		tmp[0] = (zri[1] - -2.0 - (f->x + f->fx))
			* (double)((f->zoom * f->hd) / 2.4);
		tmp[1] = (zri[0] - -1.8 - (f->y + f->fy))
			* (double)((f->zoom * f->hd) / 2.4);
		if ((r = buddha_bis(zri, cri, i + 1, f))
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

void	*set_buddha(void *d)
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
			cri[1] = xy[0] / add[2] - 2.0 + add[0];
			cri[0] = xy[1] / add[2] - 1.8 + add[1];
			buddha_bis(zri, cri, 0, &m);
		}
	return (NULL);
}
