/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 00:40:03 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/03 01:51:30 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

unsigned int	set_color(double *rgb, t_obj *obj)
{
	(void)obj;
	unsigned int	color;
	double			r;
	double			g;
	double			b;

	r = *rgb;
//	if (*rgb > obj->r)
//		r = obj->r;
	++rgb;
	g = *rgb;
//	if (*rgb > obj->g)
//		g = obj->g;
	++rgb;
	b = *rgb;
//	if (*rgb > obj->b)
//		b = obj->b;
	color = 0;
	color = ((color | (unsigned char)r) << 8);
	color = ((color | (unsigned char)g) << 8);
	color = ((color | (unsigned char)b));
	return (color);
}
