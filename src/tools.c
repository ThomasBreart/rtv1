/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 07:34:50 by tbreart           #+#    #+#             */
/*   Updated: 2016/09/30 19:04:48 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ft_carre(double x)
{
	x *= x;
	return (x);
}

void	vector_normalize(t_vec3d *v)
{
	double	id;

	id = 1.0 / sqrt( (v->x * v->x) + (v->y * v->y) + (v->z * v->z) );
	v->x *= id;
	v->y *= id;
	v->z *= id;
}

double	vector_dot(t_vec3d *a, t_vec3d *b)
{
	double	tmp;

	tmp = a->x * b->x + a->y * b->y + a->z * b->z;
	return (tmp);
}

t_vec3d	*vector_copy(t_vec3d *a)
{
	t_vec3d		*v;

	v = (t_vec3d*)malloc(sizeof(t_vec3d));
	v->x = a->x;
	v->y = a->y;
	v->z = a->z;
	return (v);
}

t_vec3d		vector_sub(t_vec3d a, t_vec3d b)
{
	t_vec3d		v;
	
	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return (v);
}

t_vec3d		vector_add(t_vec3d a, t_vec3d b)
{
	t_vec3d		v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return (v);
}

t_vec3d		vector_init(double x, double y, double z)
{
	t_vec3d		vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3d		cross_product(t_vec3d a, t_vec3d b)
{
	t_vec3d		c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = (a.z * b.x) - (a.x * b.z);
	c.z = (a.x * b.y) - (a.y * b.x);
	return (c);
}

t_vec3d		vector_multiply_real(t_vec3d a, double b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
	return (a);
}
/*
t_vec3d		vector_multiply(t_vec3d a, t_vec3d b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}*/
