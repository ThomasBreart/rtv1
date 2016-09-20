/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 07:52:21 by tbreart           #+#    #+#             */
/*   Updated: 2016/09/20 08:44:41 by tbreart          ###   ########.fr       */
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
	vector_sub(dist, &ray->o);
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

int		expose_hook(t_mlx *mlx)
{
	t_var	*var;
	int		y;
	int		x;
	t_vec3d		target;
	t_vec3d		ray_direction;
	t_ray		ray;
	double		coef;

	var= get_var();
	y = 0;
	while (y < var->win_ord)
	{
		x = 0;
		while (x < var->win_abs)
		{
			target.x = x - (var->win_abs / 2);
			target.y = y - (var->win_ord / 2);
			target.z = -(var->win_abs / (2 * tan(var->cam_d_z / 2)));
			vector_normalize(&target);

			ray_direction.x = target.x - var->cam_o.x;
			ray_direction.y = target.y - var->cam_o.y;
			ray_direction.z = target.z - var->cam_o.z;
			vector_normalize(&ray_direction);

			ray = create_ray(var->cam_o, ray_direction);
			coef = 20000;
			if (intersection_sphere(&var->sphere, &ray, &coef) != -1 && coef < 20000)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, mlx_get_color_value(mlx->mlx, 0xFF0000));
//				img_pixel_put(mlx, x, y, 1);//sphere touchay !
			++x;
		}
		++y;
	}
	return (0);
}
