/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 22:20:31 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/24 04:19:19 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		result;
	char	sign;
	int		base;

	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r')
		str += 1;
	base = (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) ? 16 : 10;
	base == 16 ? str += 2 : str;
	if (*str == '-' || *str == '+')
	{
		sign = *str;
		str += 1;
	}
	while ((*str >= '0' && *str <= '9') || (base == 16 && *str >= 'A'
				&& *str <= 'F'))
	{
		result = (base == 16 && *str >= 'A' && *str <= 'F') ?
			result * base + *str - 'A' + 10 : result * base + *str - '0';
		str += 1;
	}
	return (sign == '-' ? -result : result);
}
