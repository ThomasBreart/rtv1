/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 00:40:03 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/06 13:51:23 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

unsigned int	set_color(double *rgb)
{
	unsigned int	color;
	double			r;
	double			g;
	double			b;

	r = *rgb;
	++rgb;
	g = *rgb;
	++rgb;
	b = *rgb;
	color = 0;
	color = ((color | (unsigned char)r) << 8);
	color = ((color | (unsigned char)g) << 8);
	color = ((color | (unsigned char)b));
	return (color);
}
