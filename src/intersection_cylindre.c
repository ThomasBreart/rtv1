/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylindre.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 11:33:26 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/21 01:27:52 by tbreart          ###   ########.fr       */
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

int			intersection_cylinder(t_obj *cylinder, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		delta;
	t_vec3d		x;

	x = vector_sub(ray->o, cylinder->origin);
	a = vector_dot(&ray->d, &ray->d) -
							ft_carre(vector_dot(&ray->d, &cylinder->normale));
	b = 2.0 * (vector_dot(&ray->d, &x) -
			(vector_dot(&ray->d, &cylinder->normale) *
										vector_dot(&x, &cylinder->normale)));
	c = vector_dot(&x, &x) - ft_carre(vector_dot(&x, &cylinder->normale)) -
													ft_carre(cylinder->radius);
	delta = ft_carre(b) - (4.0 * a * c);
	if (delta < 0)
		return (0);
	else
		return (delta_pos(a, b, delta, &ray->lenght));
}
