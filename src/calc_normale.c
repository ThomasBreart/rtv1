/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:39:22 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/06 13:49:36 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		calc_cylinder_normale(t_ray *light_ray, t_vec3d hit,
															t_vec3d *normale)
{
	t_vec3d		tmp;
	double		m;

	tmp = vector_multiply_real(light_ray->obj->normale, light_ray->lenght);
	m = vector_dot(&light_ray->d, &tmp);
	tmp = vector_sub(light_ray->o, light_ray->obj->origin);
	m += vector_dot(&tmp, &light_ray->obj->normale);
	*normale = vector_sub(hit, light_ray->obj->origin);
	*normale = vector_sub(*normale,
							vector_multiply_real(light_ray->obj->normale, m));
}

static void		calc_cone_normale(t_ray *light_ray, t_vec3d hit,
															t_vec3d *normale)
{
	t_vec3d		tmp;
	double		m;

	tmp = vector_multiply_real(light_ray->obj->normale, light_ray->lenght);
	m = vector_dot(&light_ray->d, &tmp);
	tmp = vector_sub(light_ray->o, light_ray->obj->origin);
	m += vector_dot(&tmp, &light_ray->obj->normale);
	*normale = vector_sub(hit, light_ray->obj->origin);
	tmp = vector_multiply_real(light_ray->obj->normale,
				((1.0 + light_ray->obj->radius * light_ray->obj->radius) * m));
	*normale = vector_sub(*normale, tmp);
}

void			calc_normale(t_ray *light_ray, t_vec3d hit, t_vec3d *normale)
{
	if (light_ray->obj->type == SPHERE)
		*normale = vector_sub(hit, light_ray->obj->origin);
	else if (light_ray->obj->type == PLAN)
		*normale = light_ray->obj->normale;
	else if (light_ray->obj->type == CYLINDER)
		calc_cylinder_normale(light_ray, hit, normale);
	else if (light_ray->obj->type == CONE)
		calc_cone_normale(light_ray, hit, normale);
}
