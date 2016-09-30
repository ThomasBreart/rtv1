/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 07:52:21 by tbreart           #+#    #+#             */
/*   Updated: 2016/09/30 19:49:07 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	create_ray(t_vec3d o, t_vec3d d)
{
	t_ray	ray;

	ray.o = o;// pas sur de l assignation structure
	ray.d = d;
	return (ray);
}
/*
int		intersection_sphere(t_sphere *sphere, t_ray *ray, double *coef)
{
	t_vec3d		*dist;
	double		b;
	double		d;
	double		t0;
	double		t1;
	int			result;

	result = -1;
	dist = vector_copy(&sphere->position);
	*dist = vector_sub(*dist, ray->o);
	b = vector_dot(&ray->d, dist);
	d = b * b - vector_dot(dist, dist) + sphere->radius * sphere->radius;
	if (d < 0)
		return (result);
	t0 = b - sqrt(d);
	t1 = b + sqrt(d);
	if (t0 > 0.1 && t0 < *coef)
	{
		*coef = t0;
		result = 1; // return a la place ?
	}
	if (t1 > 0.1 && t1 < *coef)
	{
		*coef = t1;
		result = 1;
	}
	return (result);
}
*/

int		intersection_sphere(t_sphere *sphere, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t1;
	double		t2;
	double		hit;

	a = ray->d.x * ray->d.x + ray->d.y * ray->d.y + ray->d.z * ray->d.z;
	b = 2 * (ray->d.x * (ray->o.x - sphere->origin.x) + ray->d.y * (ray->o.y - sphere->origin.y) + ray->d.z * (ray->o.z - sphere->origin.z));
	c = ft_carre(ray->o.x - sphere->origin.x) + ft_carre(ray->o.y - sphere->origin.y) + ft_carre(ray->o.z - sphere->origin.z) - ft_carre(sphere->radius);

	delta = ft_carre(b) - 4 * a * c;
	if (delta < 0)
		return (0);
	if (delta == 0)
		hit = b * -1 / 2 * a;
	else
	{
		t1 = (b * -1 + sqrt(delta)) / 2 * a;
		t2 = (b * -1 - sqrt(delta)) / 2 * a;
		if (t1 < t2)
			hit = t1;
		else
			hit = t2;
	}
	return (1);
}

int		expose_hook(t_mlx *mlx)
{
	t_var	*var;
	int		y;
	int		x;
	t_vec3d		target;
	t_vec3d		ray_direction;
	t_ray		ray;
//	double		coef;

	var= get_var();
	y = 0;
	while (y < var->win_ord)
	{
		x = 0;
		while (x < var->win_abs)
		{
			target = vector_add(var->cam.viewplane_upleft, vector_multiply_real(var->cam.rightvec, var->cam.xindent * x));
			target = vector_sub(target, vector_multiply_real(var->cam.upvec, var->cam.yindent * y));
		/*	target.x = x - (var->win_abs / 2);
			target.y = y - (var->win_ord / 2);
			target.z = -(var->win_abs / (2 * tan(var->cam_d_z / 2)));*/
			vector_normalize(&target);

	/*		ray_direction.x = target.x - var->cam_o.x;
			ray_direction.y = target.y - var->cam_o.y;
			ray_direction.z = target.z - var->cam_o.z;*/
			ray_direction = vector_sub(target, var->cam.origin);
			vector_normalize(&ray_direction);

			ray = create_ray(var->cam.origin, ray_direction);
		//	coef = 20000;
			if (intersection_sphere(&var->sphere, &ray) == 1)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, mlx_get_color_value(mlx->mlx, 0xFF0000));
//				img_pixel_put(mlx, x, y, 1);//sphere touchay !
			++x;
		}
		++y;
	}
	return (0);
}
