/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:38:47 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/05 22:49:46 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		delta_zero(double a, double b, double *near)
{
	double		hit;

	hit = b * -1.0 / (2.0 * a);
	if (hit < *near)
	{
		*near = hit;
		return (1);
	}
	return (0);
}

static int		delta_pos(double a, double b, double delta, double *near)
{
	double		t1;
	double		t2;
	double		hit;

	t1 = ((b * -1.0) + sqrt(delta)) / (2.0 * a);
	t2 = ((b * -1.0) - sqrt(delta)) / (2.0 * a);
	if (t1 < t2)
		hit = t1;
	else
		hit = t2;
	if (hit < *near)
	{
		*near = hit;
		return (1);
	}
	return (0);
}

int		intersection_sphere(t_obj *sphere, t_ray *ray, double *near)
{
	double		a;
	double		b;
	double		c;
	double		delta;

	a = ray->d.x * ray->d.x + ray->d.y * ray->d.y + ray->d.z * ray->d.z;
	b = 2.0 * (ray->d.x * (ray->o.x - sphere->origin.x) +
		ray->d.y * (ray->o.y - sphere->origin.y) +
		ray->d.z * (ray->o.z - sphere->origin.z));
	c = ft_carre(ray->o.x - sphere->origin.x) +
		ft_carre(ray->o.y - sphere->origin.y) +
		ft_carre(ray->o.z - sphere->origin.z) - ft_carre(sphere->radius);
	delta = ft_carre(b) - (4.0 * a * c);
	if (delta < 0)
		return (0);
	if (delta == 0)
		return (delta_zero(a, b, near));
	else
		return (delta_pos(a, b, delta, near));
	return (0);
}
