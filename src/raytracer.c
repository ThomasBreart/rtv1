/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 00:07:45 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/06 12:18:47 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		shoot_obj(t_scene *scene, t_ray *ray)
{
	int		i;

	i = 0;
	while (i <= scene->obj_index)
	{
		if (scene->obj[i].type == SPHERE &&
							intersection_sphere(&scene->obj[i], ray) == 1)
			ray->obj = &scene->obj[i];
		else if (scene->obj[i].type == PLAN &&
								intersection_plan(&scene->obj[i], ray) == 1)
			ray->obj = &scene->obj[i];
		else if (scene->obj[i].type == CYLINDER &&
							intersection_cylinder(&scene->obj[i], ray) == 1)
			ray->obj = &scene->obj[i];
		else if (scene->obj[i].type == CONE &&
								intersection_cone(&scene->obj[i], ray) == 1)
			ray->obj = &scene->obj[i];
		++i;
	}
}

static int		raytracer_lights(t_scene *scene, t_ray *cam_ray)
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
		if (cam_ray->obj == light_ray.obj)
			find_color(&light_ray, &scene->light[i], hit, (double*)&rgb, cam_ray);
		++i;
	}
	color = set_color((double*)&rgb, cam_ray->obj);
	return (color);
}

void			raytracer(t_mlx *mlx, t_scene *scene, t_var *var)
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
/*				if (cam_ray.obj->origin.z == 50)
					color = 255;
				else
					color = 255 * 255;*/
				color = raytracer_lights(scene, &cam_ray);
				img_pixel_put(mlx, x, y, color);
			}
			++x;
		}
		++y;
	}
}
