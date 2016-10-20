/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 01:33:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/21 01:33:21 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
