/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 09:39:37 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/21 01:29:31 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	delta_pos(double a, double b, double delta, double *near)
{
	double		t1;
	double		t2;
	double		hit;

	t1 = ((b * -1.0) + sqrt(delta)) / (2.0 * a);
	t2 = ((b * -1.0) - sqrt(delta)) / (2.0 * a);
	if (t1 < 0 && t2 < 0)
		return (0);
	if (t1 < t2 && t1 > 0)
		hit = t1;
	else
		hit = t2;
	if (hit < *near && hit > 0)
	{
		*near = hit;
		return (1);
	}
	return (0);
}

int			intersection_cone(t_obj *cone, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		tmp;
	t_vec3d		x;

	x = vector_sub(ray->o, cone->origin);
	tmp = (1.0 + cone->radius * cone->radius) *
								ft_carre(vector_dot(&ray->d, &cone->normale));
	a = vector_dot(&ray->d, &ray->d) - tmp;
	tmp = (1.0 + cone->radius * cone->radius) *
		vector_dot(&ray->d, &cone->normale) * vector_dot(&x, &cone->normale);
	b = 2.0 * (vector_dot(&ray->d, &x) - tmp);
	tmp = (1.0 + cone->radius * cone->radius) *
									ft_carre(vector_dot(&x, &cone->normale));
	c = vector_dot(&x, &x) - tmp;
	tmp = ft_carre(b) - (4.0 * a * c);
	if (tmp < 0)
		return (0);
	else
		return (delta_pos(a, b, tmp, &ray->lenght));
}
