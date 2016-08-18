/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 08:55:59 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/28 07:39:23 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_gen(t_gen *gen)
{
	if (!(gen->mlx = mlx_init()))
		error(1);
	gen->rep = 0;
}

int		release_fct(int button, int x, int y, t_fract *f)
{
	long double	fx;
	long double	fy;

	fx = (long double)x;
	fy = (long double)y;
	if (button == 1 && (f->rep & 0x2))
	{
		f->rep ^= 0x2;
		f->x += f->fx;
		f->y += f->fy;
		f->fx = 0;
		f->fy = 0;
		mlx_clear_window(f->mlx, f->win);
		prev_f(f);
	}
	return (0);
}

void	zoom_fct(int button, long double fx, long double fy, t_fract *f)
{
	if (button == 4 || button == 7)
	{
		f->zoom *= 2.0;
		f->x += fx / (f->zoom / (2.4));
		f->y += fy / (f->zoom / (2.4));
		if (f->f != &set_buddha && f->f != &set_ghost && f->f != &set_jghost
				&& f->f != &set_light)
			f->i_max += 4;
	}
	if (button == 2 || button == 5 || button == 6)
	{
		f->x -= fx / (f->zoom / (2.4));
		f->y -= fy / (f->zoom / (2.4));
		f->zoom /= 2.0;
		if (f->i_max > 5 && f->f != &set_buddha && f->f != &set_ghost
				&& f->f != &set_jghost && f->f != &set_light)
			f->i_max -= 4;
	}
	mlx_clear_window(f->mlx, f->win);
	prev_f(f);
}

int		button_function(int button, int x, int y, t_fract *f)
{
	long double	fx;
	long double	fy;

	fx = (long double)x;
	fy = (long double)y;
	if (button == 1 && !(f->rep & 0x2))
	{
		f->sx = x;
		f->sy = y;
		f->rep ^= 0x2;
	}
	if (button == 2 || button == 5 || button == 6 || button == 7)
		zoom_fct(button, fx, fy, f);
	return (0);
}

void	init_thread(t_fract *f)
{
	int	i;

	i = -1;
	while (++i < MT)
	{
		f->m[i].m = f;
		f->m[i].lim[0] = (i * (X / MT));
		f->m[i].lim[1] = (f->m[i].lim[0] + (X / MT));
	}
}
