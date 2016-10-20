/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:34:47 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/21 01:07:33 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		is_hexa(char c)
{
	if ((c >= '0' && c <= '9') ||
		(c >= 'A' && c <= 'F') ||
		(c >= 'a' && c <= 'f'))
		return (1);
	return (0);
}

double	convert(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else
		return (c - 'a' + 10);
}

double	ft_atod_h(char *str)
{
	double		nb;

	nb = 0;
	while (ft_isblank(*str))
		str++;
	while (is_hexa(*str))
	{
		nb = nb * 16 + convert(*str);
		++str;
	}
	return (nb);
}
