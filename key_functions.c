/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 15:47:12 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/29 02:05:11 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	color_set(int key, t_fract *f)
{
	if (key == 12)
	{
		f->rep ^= 0x4;
		if (f->rep & 0x4 || f->f == &set_buddha || f->f == &set_ghost
			|| f->f == &set_jghost || f->f == &set_light)
		{
			f->c = 0x00;
			f->r = 0x30;
			f->v = 0xff;
			f->b = 0xff;
		}
		else
		{
			f->r = 0x00;
			f->v = 0x50;
			f->b = 0x05;
		}
	}
}

static void	key_function_bis_2(int key, t_fract *f)
{
	if (key == 32)
		f->i_max -= 5;
	else if (key == 8)
		clear(f);
	else if (key == 15)
		f->r += 2;
	else if (key == 17)
		f->r -= 2;
	else if (key == 9 && f->v < 254)
		f->v += 2;
	else if (key == 45 && f->v > 1)
		f->v -= 2;
	else if (key == 11 && f->v < 254)
		f->b += 2;
	else if (key == 46 && f->v > 1)
		f->b -= 2;
	else if (key == 0)
		f->rep ^= 0x10;
	else if (key == 6)
		f->rep ^= 0x100;
	else if (key == 2)
		f->c += 2;
	else if (key == 7)
		f->c -= 2;
}

static void	change_fractal(t_fract *f)
{
	if (f->f == &set_mandelbrot)
		f->f = &set_julia;
	else if (f->f == &set_julia)
		f->f = &set_burn;
	else if (f->f == &set_burn)
		f->f = &set_bjulia;
	else if (f->f == &set_bjulia)
		f->f = &set_buddha;
	else if (f->f == &set_buddha)
		f->f = &set_ghost;
	else if (f->f == &set_ghost)
		f->f = &set_jghost;
	else if (f->f == &set_jghost)
		f->f = &set_light;
	else if (f->f == &set_light)
		f->f = &set_mandelbrot;
	clear(f);
}

static void	key_function_bis(int key, t_fract *f)
{
	if (key == 53)
		exit(1);
	else if (key == 31)
		change_fractal(f);
	else if (key == 49)
		f->rep ^= 0x1;
	else if (key == 123)
		f->x -= 0.1 / (f->zoom / Y);
	else if (key == 124)
		f->x += 0.1 / (f->zoom / Y);
	else if (key == 126)
		f->y -= 0.1 / (f->zoom / Y);
	else if (key == 125)
		f->y += 0.1 / (f->zoom / Y);
	else if (key == 34)
		f->i_max += 5;
	else if (key == 5)
		f->rep ^= 0x200;
	else if (key == 4 && f->hd < 7)
		f->hd += 1;
	else if (key == 38)
		f->hd = 1;
}

int			key_function(int key, t_fract *f)
{
	if (key == 53 || key == 31 || key == 49 || key == 4 || key == 123
			|| key == 124 || key == 126 || key == 125 || key == 34
			|| key == 5 || key == 38)
	{
		key_function_bis(key, f);
		mlx_clear_window(f->mlx, f->win);
		prev_f(f);
	}
	else if ((key == 32 && f->i_max > 5) || key == 8
		|| (key == 15 && f->r < 254)
		|| (key == 17 && f->r > 1) || key == 9 || (key == 45) || (key == 11)
		|| (key == 46) || key == 0 || key == 6 || key == 7 || key == 2)
	{
		key_function_bis_2(key, f);
		mlx_clear_window(f->mlx, f->win);
		prev_f(f);
	}
	else if (key == 12)
	{
		color_set(key, f);
		mlx_clear_window(f->mlx, f->win);
		prev_f(f);
	}
	return (0);
}
