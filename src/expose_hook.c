/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 07:52:21 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/05 23:56:22 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	create_ray(t_vec3d o, t_vec3d d)
{
	t_ray	ray;

	ray.o = o;
	ray.d = d;
	return (ray);
}

void	shoot_obj(t_scene *scene, t_ray *ray, t_near *near)
{
	int		i;

	i = 0;
	while (i <= scene->obj_index)
	{
		if (scene->obj[i].type == SPHERE)
		{
			if (intersection_sphere(&scene->obj[i], ray, &near->lenght) == 1)
				near->obj = &scene->obj[i];
		}
		else if (scene->obj[i].type == PLAN)
		{
			if (intersection_plan(&scene->obj[i], ray, &near->lenght) == 1)
				near->obj = &scene->obj[i];
		}
		++i;
	}
}

int		find_color(t_near near, t_ray ray, t_light light, t_vec3d hit)
{
	t_vec3d		normale;
	double		angle;
	double		r;
	double		g;
	double		b;
	int			color;

	color = 0;
	if (near.obj->type == SPHERE)
		normale = vector_sub(hit, near.obj->origin);
	else if (near.obj->type == PLAN)
		normale = near.obj->normale;
	vector_normalize(&normale);
	angle = vector_dot(&normale, &ray.d);
	if (angle >= 0)
	{
		r = 0;
		g = 255;
		b = 0;
	}
	if (angle < 0)
	{
		angle *= -1;
		r = near.obj->r * light.r / 255.0 * angle;
		g = near.obj->g * light.g / 255.0 * angle;
		b = near.obj->b * light.b / 255.0 * angle;
	}
	color = ((color | (unsigned char)r)<< 8);
	color = ((color | (unsigned char)g)<< 8);
	color = ((color | (unsigned char)b));
	return (color);
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
	t_near		near2;
	int			s;
	int			i;
	int			color;
	t_vec3d		hit;
	t_light		light;

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
			target = vector_add(scene->cam.viewplane_upleft, vector_multiply_real(scene->cam.rightvec, scene->cam.xindent * x));
			target = vector_sub(target, vector_multiply_real(scene->cam.upvec, scene->cam.yindent * y));
			vector_normalize(&target);
			ray_direction = vector_sub(target, scene->cam.origin);
			vector_normalize(&ray_direction);

			ray = create_ray(scene->cam.origin, target); // target ou ray_direction ?
			shoot_obj(scene, &ray, &near);
			if (near.obj != NULL)
			{
				color = 0;
				hit = vector_multiply_real(ray.d, near.lenght);
				hit = vector_add(scene->cam.origin, hit);
				//while light
				light.origin.x = 0;
				light.origin.y = -3.5;
				light.origin.z = 30;
				light.r = 255;
				light.g = 255;
				light.b = 255;
				ray.o = light.origin;
				ray.d = vector_sub(hit, ray.o);
				vector_normalize(&ray.d);
				i = 0;
				near2.lenght = 20000;
				near2.obj = NULL;
				shoot_obj(scene, &ray, &near2);
				if (near.obj ==  near2.obj)
					color = find_color(near, ray, light, hit);
				else
					color = 255;
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
			}
			++x;
		}
		++y;
	}
	return (0);
}
