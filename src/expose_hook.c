/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 07:52:21 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/18 15:19:45 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	shoot_obj(t_scene *scene, t_ray *ray)
{
	int		i;

	i = 0;
	while (i <= scene->obj_index)
	{
		if (scene->obj[i].type == SPHERE)
		{
			if (intersection_sphere(&scene->obj[i], ray) == 1)
				ray->obj = &scene->obj[i];
		}
		else if (scene->obj[i].type == PLAN)
		{
			if (intersection_plan(&scene->obj[i], ray) == 1)
				ray->obj = &scene->obj[i];
		}
		else if (scene->obj[i].type == CYLINDER)
		{
			if (intersection_cylinder(&scene->obj[i], ray) == 1)
				ray->obj = &scene->obj[i];
		}
		else if (scene->obj[i].type == CONE)
		{
			if (intersection_cone(&scene->obj[i], ray) == 1)
				ray->obj = &scene->obj[i];
		}
		++i;
	}
}

void		find_color(t_ray *light_ray, t_light light, t_vec3d hit, double *rgb)
{
	t_vec3d		normale;
	t_vec3d		tmp;
	double		angle;
	int			color;
	double		m;
	t_scene		*scene;

	scene = get_scene();
	color = 0;
	if (light_ray->obj->type == SPHERE)
		normale = vector_sub(hit, light_ray->obj->origin);
	else if (light_ray->obj->type == PLAN)
		normale = light_ray->obj->normale;
	else if (light_ray->obj->type == CYLINDER)
	{
		tmp = vector_multiply_real(light_ray->obj->normale, light_ray->lenght);
		m = vector_dot(&light_ray->d, &tmp);
		tmp = vector_sub(light.origin, /*hit*/light_ray->obj->origin);
		m += vector_dot(&tmp, &light_ray->obj->normale);
		normale = vector_sub(hit, light_ray->obj->origin);
		normale = vector_sub(normale, vector_multiply_real(light_ray->obj->normale, m));
	}
	else if (light_ray->obj->type == CONE)
	{
		tmp = vector_multiply_real(light_ray->obj->normale, light_ray->lenght);
		m = vector_dot(&light_ray->d, &tmp);
		tmp = vector_sub(light.origin, /*hit*/light_ray->obj->origin);
		m += vector_dot(&tmp, &light_ray->obj->normale);
		normale = vector_sub(hit, light_ray->obj->origin);
		tmp = vector_multiply_real(light_ray->obj->normale, ((1.0 + light_ray->obj->radius * light_ray->obj->radius) * m));
		normale = vector_sub(normale, tmp);
	}
	vector_normalize(&normale);
	angle = vector_dot(&normale, &light_ray->d);
/*	if (angle >= 0 && light_ray->obj->type == PLAN)
	{
		normale = vector_multiply_real(normale, -1.0);
		angle = vector_dot(&normale, &light_ray->d);
	}*/
	if (angle >= 0)
	{
		*rgb = 0;
		++rgb;
		*rgb = 255;
		++rgb;
		*rgb = 0;
	}
	if (angle < 0)
	{
		angle *= -1;
		*rgb += light_ray->obj->r * light.r / 255.0 * angle;
		++rgb;
		*rgb += light_ray->obj->g * light.g / 255.0 * angle;
		++rgb;
		*rgb += light_ray->obj->b * light.b / 255.0 * angle;
	}
}

unsigned int		set_color(double *rgb, t_obj *obj)
{
	unsigned int		color;
	double	r;
	double	g;
	double	b;

	r = *rgb;
	if (*rgb > obj->r)
		r = obj->r;
	++rgb;
	g = *rgb;
	if (*rgb > obj->g)
		g = obj->g;
	++rgb;
	b = *rgb;
	if (*rgb > obj->b)
		b = obj->b;
	color = 0;
	color = ((color | (unsigned char)r)<< 8);
	color = ((color | (unsigned char)g)<< 8);
	color = ((color | (unsigned char)b));
	return (color);
}

int		raytracer_lights(t_scene *scene, t_ray *cam_ray/*, int x, int y*/)
{
	t_vec3d			hit;
	t_ray			light_ray;
	double			rgb[3];
	unsigned int	color;
	int				i;

	hit = vector_multiply_real(cam_ray->d, cam_ray->lenght);
	hit = vector_add(scene->cam.origin, hit);
	i = 0;
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	while (i <= scene->light_index)
	{
		light_ray = create_light_ray(&scene->light[i], hit);
		shoot_obj(scene, &light_ray);
		if (cam_ray->obj ==  light_ray.obj)
			find_color(&light_ray, scene->light[i], hit, (double*)&rgb);
		else
		{
			printf("p null jepari: %p\n", light_ray.obj);
		//	if (cam_ray->obj->type == CONE)
		//	{
		//		printf("obj touchay: %d\n", light_ray.obj->type);
				rgb[0] = 250;
		//	}
		}
		++i;
	}
	color = set_color((double*)&rgb, cam_ray->obj);
	return (color);
}

void	raytracer(t_mlx *mlx, t_scene *scene, t_var *var)
{
	int				y;
	int				x;
	t_ray			cam_ray;
	unsigned int	color;

	y = 0;
	while (y < var->win_ord)
	{
		x = 0;
		while (x < var->win_abs)
		{
			cam_ray = create_cam_ray(x, y);
			shoot_obj(scene, &cam_ray);
			if (cam_ray.obj != NULL)
			{
				color = raytracer_lights(scene, &cam_ray/*, x, y*/);
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
