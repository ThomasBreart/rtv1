/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 00:17:56 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/06 13:50:24 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		calc_color(double angle, t_ray *light_ray, t_light *light,
																	double *rgb)
{
	angle *= -1;
	*rgb += light_ray->obj->r * light->r / 255.0 * angle;
	++rgb;
	*rgb += light_ray->obj->g * light->g / 255.0 * angle;
	++rgb;
	*rgb += light_ray->obj->b * light->b / 255.0 * angle;
}

static double	calc_spec(t_scene *scene, t_vec3d hit, t_ray *light_ray,
																t_vec3d normale)
{
	t_vec3d		view_vec;
	t_vec3d		r_vec;
	t_vec3d		v_vec;
	t_vec3d		tmpvec;
	double		tmp;

	view_vec = vector_sub(scene->cam.origin, hit);
	tmpvec = vector_multiply_real(normale, -1);
	v_vec = vector_multiply_real(normale, (2 * vector_dot(&tmpvec,
															&light_ray->d)));
	r_vec = vector_add(light_ray->d, v_vec);
	vector_normalize(&r_vec);
	vector_normalize(&view_vec);
	tmp = vector_dot(&r_vec, &view_vec);
	if (tmp <= 0)
		return (-1);
	tmp = ft_pow(tmp, 80);
	return (tmp);
}

static void		spec_color(t_light *light, double *rgb, double spec)
{
	*rgb += light->r * spec;
	++rgb;
	*rgb += light->g * spec;
	++rgb;
	*rgb += light->b * spec;
}

static void		adjust_color_intensity(double *rgb)
{
	if (*rgb > 255)
		*rgb = 255;
	++rgb;
	if (*rgb > 255)
		*rgb = 255;
	++rgb;
	if (*rgb > 255)
		*rgb = 255;
}

void			find_color(t_ray *light_ray, t_light *light, t_vec3d hit,
																	double *rgb)
{
	t_vec3d		normale;
	double		angle;
	int			color;
	t_scene		*scene;
	double		spec;

	scene = get_scene();
	color = 0;
	calc_normale(light_ray, hit, &normale);
	vector_normalize(&normale);
	angle = vector_dot(&normale, &light_ray->d);
	if (angle >= 0 && light_ray->obj->type == PLAN)
	{
		normale = vector_multiply_real(normale, -1.0);
		angle = vector_dot(&normale, &light_ray->d);
	}
	if (angle < 0)
	{
		calc_color(angle, light_ray, light, rgb);
		if ((spec = calc_spec(scene, hit, light_ray, normale)) > 0)
			spec_color(light, rgb, spec);
		adjust_color_intensity(rgb);
	}
}
