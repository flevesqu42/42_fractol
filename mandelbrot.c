/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 17:37:59 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/28 07:42:13 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_gen *gen)
{
	if (!(gen->mandelbrot.win = mlx_new_window(gen->mlx, X, Y
					, "Fract'ol - origin : mandelbrot")))
		error(2);
	if (!(gen->mandelbrot.img = mlx_new_image(gen->mlx, X, Y)))
		error(4);
	init_thread(&gen->mandelbrot);
	clear(&gen->mandelbrot);
	gen->mandelbrot.rep = 0;
	gen->mandelbrot.r = 0x00;
	gen->mandelbrot.v = 0x50;
	gen->mandelbrot.b = 0x05;
	gen->mandelbrot.tab = NULL;
	gen->mandelbrot.f = &set_mandelbrot;
	gen->mandelbrot.mlx = gen->mlx;
	gen->mandelbrot.data = mlx_get_data_addr(gen->mandelbrot.img
			, &gen->mandelbrot.bpp, &gen->mandelbrot.size_line
			, &gen->mandelbrot.endian);
	prev_f(&gen->mandelbrot);
	mlx_hook(gen->mandelbrot.win, 17, (1l << 0), exit_fct, &gen->mandelbrot);
	mlx_hook(gen->mandelbrot.win, 2, (1l << 0), key_function, &gen->mandelbrot);
	mlx_hook(gen->mandelbrot.win, 4, (1l << 13), button_function
				, &gen->mandelbrot);
	mlx_hook(gen->mandelbrot.win, 5, (1l << 13), release_fct, &gen->mandelbrot);
	mlx_hook(gen->mandelbrot.win, 6, (1l << 6), move_function
				, &gen->mandelbrot);
}

void	clear(t_fract *f)
{
	f->x = 0;
	f->y = 0;
	f->fy = 0;
	f->fx = 0;
	f->i_max = f->f == &set_buddha || f->f == &set_ghost || f->f == &set_jghost
		|| f->f == &set_light ? 100 : 25;
	f->zoom = Y;
}

void	prev_f(t_fract *f)
{
	pthread_t	t[MT];
	int			y;
	int			i;

	if (f->f == &set_buddha || f->f == &set_ghost || f->f == &set_jghost
		|| f->f == &set_light)
	{
		prev_buddha(f);
		return ;
	}
	y = -1;
	while (++y < MT)
		pthread_create(&t[y], NULL, f->f, &f->m[y]);
	i = -1;
	while (++i < MT)
		pthread_join(t[i], NULL);
	y = -1;
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	ft_bzero(f->data, f->size_line * Y);
}

void	mandelbrot_bis(long double *zri, long double *cri
	, int *xy, t_fract *f)
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
		zri[1] = 2 * zri[1] * tmp[0] + cri[1];
		++i;
	}
	if (i < f->i_max || (f->rep & 0x10))
	{
		i = f->rep & 0x100 ? f->i_max - i : i;
		img_pixel_put(f, xy[0], xy[1], f->rep & 0x4 ? color(i, f) : i * col);
	}
}

void	*set_mandelbrot(void *d)
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
	add[2] = (double)m.zoom / (2.4);
	xy[1] = -1;
	while (++xy[1] < Y && (xy[0] = xy[2] - 1))
		while (++xy[0] < xy[3] && !(zri[0] = 0)
			&& !(zri[1] = 0))
		{
			cri[0] = xy[0] / add[2] - 2.5 + add[0];
			cri[1] = xy[1] / add[2] - 1.2 + add[1];
			mandelbrot_bis(zri, cri, xy, &m);
		}
	return (NULL);
}
