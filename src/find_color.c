/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 00:17:56 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/03 03:56:10 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	t_vec3d		calc_cylinder_normale(t_ray *light_ray, t_vec3d hit)
{
	t_vec3d		tmp;
	double		m;
	t_vec3d		normale;

	tmp = vector_multiply_real(light_ray->obj->normale, light_ray->lenght);
	m = vector_dot(&light_ray->d, &tmp);
	tmp = vector_sub(light_ray->o, light_ray->obj->origin);
	m += vector_dot(&tmp, &light_ray->obj->normale);
	normale = vector_sub(hit, light_ray->obj->origin);
	normale = vector_sub(normale,
							vector_multiply_real(light_ray->obj->normale, m));
	return (normale);
}

static	t_vec3d		calc_cone_normale(t_ray *light_ray, t_vec3d hit)
{
	t_vec3d		tmp;
	double		m;
	t_vec3d		normale;

	tmp = vector_multiply_real(light_ray->obj->normale, light_ray->lenght);
	m = vector_dot(&light_ray->d, &tmp);
	tmp = vector_sub(light_ray->o, light_ray->obj->origin);
	m += vector_dot(&tmp, &light_ray->obj->normale);
	normale = vector_sub(hit, light_ray->obj->origin);
	tmp = vector_multiply_real(light_ray->obj->normale,
				((1.0 + light_ray->obj->radius * light_ray->obj->radius) * m));
	normale = vector_sub(normale, tmp);
	return (normale);
}

static	void		calc_color(double angle, t_ray *light_ray, t_light *light,
																	double *rgb)
{
	double		tmp;
	angle *= -1;
	tmp = light_ray->obj->r * light->r / 255.0 * angle;
	//*rgb += light_ray->obj->r * light->r / 255.0 * angle;
	//if (*rgb > light_ray->obj->r)
	//	*rgb = light_ray->obj->r;
	if (tmp > light_ray->obj->r)
		tmp = light_ray->obj->r;
	if (tmp > *rgb)
		*rgb = tmp;
	++rgb;
	if (tmp > light_ray->obj->g)
		tmp = light_ray->obj->g;
	if (tmp > *rgb)
		*rgb = tmp;
//	*rgb += light_ray->obj->g * light->g / 255.0 * angle;
//	if (*rgb > light_ray->obj->g)
//		*rgb = light_ray->obj->g;
	++rgb;
	if (tmp > light_ray->obj->b)
		tmp = light_ray->obj->b;
	if (tmp > *rgb)
		*rgb = tmp;
//	*rgb += light_ray->obj->b * light->b / 255.0 * angle;
//	if (*rgb > light_ray->obj->b)
//		*rgb = light_ray->obj->b;

}

double		puissance(double x, int p)
{
	int		i;
	double	tmp;

	tmp = x;
	i = 0;
	while (i < p)
	{
		x *= tmp;
		++i;
	}
	return (x);
}

void				find_color(t_ray *light_ray, t_light *light, t_vec3d hit,
																	double *rgb, t_ray *cam_ray)
{
	t_vec3d		normale;
	double		angle;
	int			color;
	t_scene		*scene;

	scene = get_scene();
	color = 0;
	if (light_ray->obj->type == SPHERE)
		normale = vector_sub(hit, light_ray->obj->origin);
	else if (light_ray->obj->type == PLAN)
		normale = light_ray->obj->normale;
	else if (light_ray->obj->type == CYLINDER)
		normale = calc_cylinder_normale(light_ray, hit);
	else if (light_ray->obj->type == CONE)
		normale = calc_cone_normale(light_ray, hit);
	vector_normalize(&normale);
	angle = vector_dot(&normale, &light_ray->d);
	if (angle >= 0 && light_ray->obj->type == PLAN)
	{
		normale = vector_multiply_real(normale, -1.0);
		angle = vector_dot(&normale, &light_ray->d);
	}
	if (angle < 0)
	{
		(void)cam_ray;
		calc_color(angle, light_ray, light, rgb);

		t_vec3d		view_vec;
		t_vec3d		r_vec;
		t_vec3d		v_vec;
		t_vec3d		tmpvec;

		view_vec = vector_sub(scene->cam.origin, hit);
		tmpvec = vector_multiply_real(normale, -1);
		v_vec = vector_multiply_real(normale, (2 * vector_dot(&tmpvec, &light_ray->d)));
		r_vec = vector_add(light_ray->d, v_vec);
		double		tmp;
		double		p;
/*
		t_vec3d		tmpvec;
		angle *= -1;
		tmpvec = vector_multiply_real(light_ray->d, -1);
		tmp = vector_dot(&tmpvec, &cam_ray->d);
	//	tmp = vector_dot(&tmp, &normale);
		tmp = puissance(tmp, 50);
		tmp = 1.0;
*/
	vector_normalize(&r_vec);
	vector_normalize(&view_vec);
	tmp = vector_dot(&r_vec, &view_vec);
	if (tmp <= 0)
		return ;
	p = puissance(tmp, 10);
	tmp = light->r * p;
	//*rgb += light->r * tmp;
	if (tmp > light->r)
		tmp = light->r;
	if (tmp > *rgb)
		*rgb = tmp;
	++rgb;
//	*rgb += light->g * tmp;
	tmp = light->g * p;
	if (tmp > light->g)
		tmp = light->g;
	if (tmp > *rgb)
		*rgb = tmp;
	++rgb;
	//*rgb += light->b * tmp;
	tmp = light->b * p;
	if (tmp > light->b)
		tmp = light->b;
	if (tmp > *rgb)
		*rgb = tmp;
	}
}
