/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 14:12:03 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/06 11:26:10 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	create_light_ray(t_light *light, t_vec3d hit)
{
	t_ray		ray;

	ray.o = light->origin;
	ray.d = vector_sub(hit, ray.o);
	vector_normalize(&ray.d);
	ray.lenght = MAX_LENGHT_RAY;
	ray.obj = NULL;
	return (ray);
}

t_ray	create_cam_ray(double x, double y)
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
