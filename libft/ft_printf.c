/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 13:19:06 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/14 13:21:02 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_printf(const char *format, ...)
{
	int		ret;
	va_list	ap;

	ret = 0;
	va_start(ap, format);
	while (*format)
	{
		while (*format && *format != '%')
		{
			pf_putchar(*format, &ret);
			format += 1;
		}
		if (*format == '%')
		{
			format += 1;
			if (read_id(&format, &ap, &ret))
				return (-1);
			if (*format)
				format += 1;
		}
	}
	va_end(ap);
	return (ret);
}

int		read_id(const char **s, va_list *ap, int *ret)
{
	t_flags		*new;
	int			bret;

	if (!(new = (t_flags*)malloc(sizeof(t_flags))))
		return (1);
	new_flags(s, ap, new);
	new->c = **s;
	if (**s == 'p')
		new->alternative = 1;
	if (**s == 'X')
		new->maj = 1;
	bret = begin_conversion(s, ap, new, ret);
	free(new);
	if (bret)
		return (1);
	return (0);
}
