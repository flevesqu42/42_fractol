/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 21:10:39 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/27 00:33:51 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		hsv(double h, double s, double v)
{
	double x;
	double m;

	m = v - (v * s);
	x = (v * s) * (1 - fabs(fmod(h / 60.0, 2) - 1.0));
	if (h < 60)
		return (((int)(((v * s) + m) * 255) << 16) + ((int)((x + m) * 255) << 8)
			+ m * 255);
	else if (h < 120)
		return (((int)((x + m) * 255) << 16) + ((int)(((v * s) + m) * 255) << 8)
			+ m * 255);
	else if (h < 180)
		return (((int)(m * 255) << 16) + ((int)(((v * s) + m) * 255) << 8)
			+ (int)((x + m) * 255));
	else if (h < 240)
		return (((int)(m * 255) << 16) + ((int)((x + m) * 255) << 8)
			+ (int)(((v * s) + m) * 255));
	else if (h < 300)
		return (((int)((x + m) * 255) << 16) + ((int)(m * 255) << 8)
			+ (int)(((v * s) + m) * 255));
	else if (h < 360)
		return (((int)(((v * s) + m) * 255) << 16) + ((int)(m * 255) << 8)
			+ (int)((x + m) * 255));
	else
		return (((int)(m * 255) << 16) + ((int)(m * 255) << 8) + (m * 255));
}

int		color(double i, t_fract *f)
{
	if (i > f->i_max)
		i = (double)f->i_max;
	return (hsv(fmod(((double)f->r / 255 * 360) * i / (double)f->i_max
		+ ((double)f->c / 255 * 360), 360)
		, 1 - ((double)f->v / 255) * i / ((double)f->i_max)
		, ((double)f->b / 255) * i / ((double)f->i_max)));
}

void	img_pixel_put(t_fract *f, int x, int y, size_t color)
{
	size_t	index;

	if (y >= Y || x >= X || x < 0 || y < 0)
		return ;
	index = (y * f->size_line) + x * (f->bpp / 8);
	f->data[index + 3] = (color & 0xFF000000) >> 24;
	f->data[index + 2] = (color & 0x00FF0000) >> 16;
	f->data[index + 1] = (color & 0x0000FF00) >> 8;
	f->data[index] = color & 0x000000FF;
}
