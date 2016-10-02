/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 07:52:21 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/02 19:46:42 by tbreart          ###   ########.fr       */
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

int		intersection_sphere(t_sphere *sphere, t_ray *ray, double *near)
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t1;
	double		t2;
	double		hit;

	a = ray->d.x * ray->d.x + ray->d.y * ray->d.y + ray->d.z * ray->d.z;
	b = 2.0 * (ray->d.x * (ray->o.x - sphere->origin.x) + ray->d.y * (ray->o.y - sphere->origin.y) + ray->d.z * (ray->o.z - sphere->origin.z));
	c = ft_carre(ray->o.x - sphere->origin.x) + ft_carre(ray->o.y - sphere->origin.y) + ft_carre(ray->o.z - sphere->origin.z) - ft_carre(sphere->radius);

	delta = ft_carre(b) - (4.0 * a * c);
	if (delta < 0)
		return (0);
	if (delta == 0)
	{
		hit = b * -1.0 / (2.0 * a);
		if (*near > hit)
		{
			*near = hit;
			return (1);
		}
	}
	else
	{
		t1 = ((b * -1.0) + sqrt(delta)) / (2.0 * a);
		t2 = ((b * -1.0) - sqrt(delta)) / (2.0 * a);
		if (t1 < t2)
			hit = t1;
		else
			hit = t2;
		if (*near > hit)
		{
			*near = hit;
			return (1);
		}
	}
	return (0);
}

int		intersection_plan(t_plan *plan, t_ray *ray, double *near)
{
	double	hit;
	double	tmp;

	hit = plan->normale.x * (ray->o.x - plan->origin.x);
	hit += plan->normale.y * (ray->o.y - plan->origin.y);
	hit += plan->normale.z * (ray->o.z - plan->origin.z);
	hit += plan->d;
	tmp = plan->normale.x * ray->d.x + plan->normale.y * ray->d.y + plan->normale.z * ray->d.z;
	hit /= tmp;
	hit *= -1;
	if (hit < *near && hit > 0)
	{
		*near = hit;
		return (1);
	}
	return (0);
}

void	object_hit(t_near *near, int type_obj, t_obj *obj)
{
	near->type_obj = type_obj;
	near->obj = obj;
}

int		expose_hook(t_mlx *mlx)
{
	t_var	*var;
	t_scene		*scene;;
	int		y;
	int		x;
	t_vec3d		target;
	t_vec3d		ray_direction;
	t_ray		ray;
	t_near		near;
	int			s;
	int			i;

	var = get_var();
	scene = get_scene();
	y = 0;
	while (y < var->win_ord)
	{
		x = 0;
		while (x < var->win_abs)
		{
			near.lenght = 20000;
			near.obj = NULL;
			s = -1;
			target = vector_add(scene->cam->viewplane_upleft, vector_multiply_real(scene->cam->rightvec, scene->cam->xindent * x));
			target = vector_sub(target, vector_multiply_real(scene->cam->upvec, scene->cam->yindent * y));
		/*	target.x = x - (var->win_abs / 2);
			target.y = y - (var->win_ord / 2);
			target.z = -(var->win_abs / (2 * tan(var->cam_d_z / 2)));*/
			vector_normalize(&target);
	/*		ray_direction.x = target.x - var->cam_o.x;
			ray_direction.y = target.y - var->cam_o.y;
			ray_direction.z = target.z - var->cam_o.z;*/
			ray_direction = vector_sub(target, scene->cam->origin);
			vector_normalize(&ray_direction);

			ray = create_ray(scene->cam->origin, target); // target ou ray_direction ?
			i = 0;
			while (i <= scene->obj_index)
			{
				if (scene->type_obj[i] == SPHERE)
				{
					if (intersection_sphere((t_sphere*)scene->obj[i], &ray, &near.lenght) == 1)
						object_hit(&near, SPHERE, scene->obj[i]);
				}
				else if (scene->type_obj[i] == PLAN)
				{
					if (intersection_plan((t_plan*)scene->obj[i], &ray, &near.lenght) == 1)
						object_hit(&near, PLAN, scene->obj[i]);
				}
				++i;
			}
			if (near.obj != NULL && near.obj->sphere.origin.x == -2)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, mlx_get_color_value(mlx->mlx, 0xFF0000));
			if (near.obj != NULL && near.obj->sphere.origin.x == 2)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, mlx_get_color_value(mlx->mlx, 0x00FF00));
			if (near.obj != NULL && near.obj->plan.origin.x == 0)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, mlx_get_color_value(mlx->mlx, 0x0000FF));
//				img_pixel_put(mlx, x, y, 1);//sphere touchay !
			++x;
		}
		++y;
	}
	return (0);
}
