/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 06:39:16 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/28 07:41:21 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <sys/types.h>
# include <pthread.h>
# define X 1600
# define Y 1000
# define MT 16
# define FRACT struct s_fract

typedef struct	s_thread
{
	int		lim[2];
	FRACT	*m;
}				t_thread;

typedef struct	s_fract
{
	int				rep;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				endian;
	int				bpp;
	int				size_line;
	int				i_max;
	long double		zoom;
	long double		x;
	long double		y;
	long double		jx;
	long double		jy;
	int				sy;
	int				sx;
	long double		fy;
	long double		fx;
	unsigned char	r;
	unsigned char	c;
	unsigned char	b;
	unsigned char	v;
	int				hd;
	void			*(*f)(void*);
	int				**tab;
	t_thread		m[MT];
}				t_fract;

typedef struct	s_gen
{
	void	*mlx;
	int		rep;
	t_fract	mandelbrot;
	t_fract	julia;
	t_fract	burn;
	t_fract	bjulia;
	t_fract	buddha;
	t_fract	ghost;
	t_fract	jghost;
	t_fract	light;
}				t_gen;

void			main_loop(int ac, char **av, t_gen *gen);
void			error(int i);
void			is_valid(char **av, t_gen *gen, int ac);
void			init_gen(t_gen *gen);
void			mandelbrot(t_gen *gen);
void			julia(t_gen *gen);
void			burning_ship(t_gen *gen);
void			bjulia(t_gen *gen);
void			buddha(t_gen *gen);
void			ghost(t_gen *gen);
void			jghost(t_gen *gen);
void			light(t_gen *gen);
int				exit_fct(void);
int				key_function(int key, t_fract *f);
int				button_function(int b, int x, int y, t_fract *f);
int				release_fct(int b, int x, int y, t_fract *f);
int				move_function(int x, int y, t_fract *f);
void			*set_mandelbrot(void *m);
void			*set_burn(void *m);
void			*set_julia(void *m);
void			*set_bjulia(void *m);
void			*set_buddha(void *m);
void			*set_ghost(void *m);
void			*set_jghost(void *m);
void			*set_light(void *m);
void			img_pixel_put(t_fract *f, int x, int y, size_t color);
void			prev_f(t_fract *m);
void			prev_buddha(t_fract *m);
void			init_thread(t_fract *m);
void			clear(t_fract *f);
void			clear_buddha(t_fract *f);
int				hsv(double h, double s, double v);
int				move_map(int x, int y, t_fract *f);
int				color(double z, t_fract *gen);

#endif
