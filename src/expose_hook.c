/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 07:52:21 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/16 12:46:08 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	create_ray(double x, double y)
{
	t_ray		ray;
	t_scene		*scene;
	t_vec3d		target;

	scene = get_scene();
	target = vector_add(scene->cam.viewplane_upleft,
			vector_multiply_real(scene->cam.rightvec, scene->cam.xindent * x));
	target = vector_sub(target,
				vector_multiply_real(scene->cam.upvec, scene->cam.yindent * y));
	target = vector_sub(target, scene->cam.origin);
	vector_normalize(&target);
	ray.o = scene->cam.origin;
	ray.d = target;
	ray.lenght = MAX_LENGHT_RAY;
	ray.obj = NULL;
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
		else if (scene->obj[i].type == CYLINDER)
		{
			if (intersection_cylinder(&scene->obj[i], ray, &near->lenght) == 1)
				near->obj = &scene->obj[i];
		}
		else if (scene->obj[i].type == CONE)
		{
			if (intersection_cone(&scene->obj[i], ray, &near->lenght) == 1)
				near->obj = &scene->obj[i];
		}
		++i;
	}
}

void		find_color(t_near near, t_ray ray, t_light light, t_vec3d hit, double *r, double *g, double *b)
{
	t_vec3d		normale;
	t_vec3d		tmp;
	double		angle;
//	double		r;
//	double		g;
//	double		b;
	int			color;
	double		m;
	t_scene		*scene;

	scene = get_scene();
	color = 0;
	if (near.obj->type == SPHERE)
		normale = vector_sub(hit, near.obj->origin);
	else if (near.obj->type == PLAN)
		normale = near.obj->normale;
	else if (near.obj->type == CYLINDER)
	{
		tmp = vector_multiply_real(near.obj->normale, near.lenght);
		m = vector_dot(&ray.d, &tmp);
		tmp = vector_sub(light.origin, /*hit*/near.obj->origin);
		m += vector_dot(&tmp, &near.obj->normale);
		normale = vector_sub(hit, near.obj->origin);
		normale = vector_sub(normale, vector_multiply_real(near.obj->normale, m));
	}
	else if (near.obj->type == CONE)
	{
		tmp = vector_multiply_real(near.obj->normale, near.lenght);
		m = vector_dot(&ray.d, &tmp);
		tmp = vector_sub(light.origin, /*hit*/near.obj->origin);
		m += vector_dot(&tmp, &near.obj->normale);
		normale = vector_sub(hit, near.obj->origin);
		tmp = vector_multiply_real(near.obj->normale, ((1 + near.obj->radius * near.obj->radius) * m));
		normale = vector_sub(normale, tmp);
		//normale = near.obj->normale;
	}
	vector_normalize(&normale);
	angle = vector_dot(&normale, &ray.d);
/*	if (angle >= 0)
	{
		*r = 0;
		*g = 255;
		*b = 0;
	}*/
	if (angle < 0)
	{
		angle *= -1;
		*r += near.obj->r * light.r / 255.0 * angle;
		*g += near.obj->g * light.g / 255.0 * angle;
		*b += near.obj->b * light.b / 255.0 * angle;
	if (*r > near.obj->r)
		*r = near.obj->r;
	if (*g > near.obj->g)
		*g = near.obj->g;
	if (*b > near.obj->b)
		*b = near.obj->b;
	}
//	return (color);
}

void	raytracer(t_mlx *mlx)
{
	t_var	*var;
	t_scene		*scene;;
	int		y;
	int		x;
//	t_vec3d		ray_direction;
	t_ray		ray;
	t_near		near;
	t_near		near2;
	int			s;
	int			i;
	unsigned int			color;
	double		r;
	double		g;
	double		b;
	t_vec3d		hit;
	//t_light		light;

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

			ray = create_ray(x, y);
			shoot_obj(scene, &ray, &near);
			if (near.obj != NULL)
			{
				hit = vector_multiply_real(ray.d, near.lenght);
				hit = vector_add(scene->cam.origin, hit);
				i = 0;
				r = 0;
				g = 0;
				b = 0;
				while (i <= scene->light_index)
				{
					ray.o = scene->light[i].origin;
					ray.d = vector_sub(hit, ray.o);
					vector_normalize(&ray.d);
					near2.lenght = 20000;
					near2.obj = NULL;
					shoot_obj(scene, &ray, &near2);
					if (near.obj ==  near2.obj)
						find_color(near, ray, scene->light[i], hit, &r, &g, &b);
					++i;
				}
				color = 0;
	color = ((color | (unsigned char)r)<< 8);
	color = ((color | (unsigned char)g)<< 8);
	color = ((color | (unsigned char)b));
			//	if (x >= 495 && x <=505 && y >= 495 && y<= 505)
			//		color = 16777215;
			//	mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
				img_pixel_put(mlx, x, y, color);
			}
			++x;
		}
		++y;
	}
}

int		expose_hook(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_ptr, 0, 0);
	return (0);
}
