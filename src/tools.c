/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 07:34:50 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 19:08:38 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ft_carre(double x)
{
	x *= x;
	return (x);
}

void		vector_normalize(t_vec3d *v)
{
	double	length;

	length = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

double		vector_dot(t_vec3d *a, t_vec3d *b)
{
	double	tmp;

	tmp = a->x * b->x + a->y * b->y + a->z * b->z;
	return (tmp);
}

t_vec3d		vector_sub(t_vec3d a, t_vec3d b)
{
	t_vec3d		v;

	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return (v);
}
