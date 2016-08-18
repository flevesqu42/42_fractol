/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 06:38:53 by flevesqu          #+#    #+#             */
/*   Updated: 2016/04/28 07:47:44 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int ac, char **av)
{
	t_gen	gen;

	if (ac == 1)
		error(5);
	gen.rep = 0;
	is_valid(av, &gen, ac);
	init_gen(&gen);
	main_loop(ac, av, &gen);
	mlx_loop(gen.mlx);
	return (0);
}

void	main_loop(int ac, char **av, t_gen *gen)
{
	while (--ac)
		if (!ft_strcmp(av[ac], "mandelbrot"))
			mandelbrot(gen);
		else if (!ft_strcmp(av[ac], "julia"))
			julia(gen);
		else if (!ft_strcmp(av[ac], "burning_ship"))
			burning_ship(gen);
		else if (!ft_strcmp(av[ac], "burning_julia"))
			bjulia(gen);
		else if (!ft_strcmp(av[ac], "buddhabrot"))
			buddha(gen);
		else if (!ft_strcmp(av[ac], "burning_ghost"))
			ghost(gen);
		else if (!ft_strcmp(av[ac], "julia_ghost"))
			jghost(gen);
		else if (!ft_strcmp(av[ac], "light"))
			light(gen);
}

void	is_valid(char **av, t_gen *gen, int ac)
{
	while (--ac)
		if ((ft_strcmp(av[ac], "mandelbrot") && ft_strcmp(av[ac], "julia"))
				&& ft_strcmp(av[ac], "burning_ship")
				&& ft_strcmp(av[ac], "burning_julia")
				&& ft_strcmp(av[ac], "buddhabrot")
				&& ft_strcmp(av[ac], "burning_ghost")
				&& ft_strcmp(av[ac], "julia_ghost")
				&& ft_strcmp(av[ac], "light"))
			error(5);
		else if (!ft_strcmp(av[ac], "mandelbrot"))
			gen->rep & 0x10 ? error(5) : (gen->rep |= 0x10);
		else if (!ft_strcmp(av[ac], "julia"))
			gen->rep & 0x20 ? error(5) : (gen->rep |= 0x20);
		else if (!ft_strcmp(av[ac], "burning_ship"))
			gen->rep & 0x40 ? error(5) : (gen->rep |= 0x40);
		else if (!ft_strcmp(av[ac], "burning_julia"))
			gen->rep & 0x80 ? error(5) : (gen->rep |= 0x80);
		else if (!ft_strcmp(av[ac], "buddhabrot"))
			gen->rep & 0x100 ? error(5) : (gen->rep |= 0x100);
		else if (!ft_strcmp(av[ac], "burning_ghost"))
			gen->rep & 0x200 ? error(5) : (gen->rep |= 0x200);
		else if (!ft_strcmp(av[ac], "julia_ghost"))
			gen->rep & 0x400 ? error(5) : (gen->rep |= 0x400);
		else if (!ft_strcmp(av[ac], "light"))
			gen->rep & 0x800 ? error(5) : (gen->rep |= 0x800);
}

void	error(int i)
{
	if (i == 1)
		ft_putstr_fd("Error : mlx_init() fail.\n", 2);
	else if (i == 2)
		ft_putstr_fd("Error : mlx_new_window() fail.\n", 2);
	else if (i == 4)
		ft_putstr_fd("Error : mlx_new_image() fail.\n", 2);
	else if (i == 5)
	{
		ft_putendl_fd("Usage:\t./fratol <valid fractal> <...>\n", 1);
		ft_putendl_fd("\t-mandelbrot", 1);
		ft_putendl_fd("\t-julia", 1);
		ft_putendl_fd("\t-burning_ship", 1);
		ft_putendl_fd("\t-burning_julia", 1);
		ft_putendl_fd("\t-buddhabrot", 1);
		ft_putendl_fd("\t-burning_ghost", 1);
		ft_putendl_fd("\t-julia_ghost", 1);
		ft_putendl_fd("\t-light\n", 1);
		ft_putendl_fd("tips: you can't open same fractal twice.", 1);
	}
	exit(1);
}

int		exit_fct(void)
{
	exit(1);
}
