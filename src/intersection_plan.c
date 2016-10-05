/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:50:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/05 22:51:15 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		intersection_plan(t_obj *plan, t_ray *ray, double *near)
{
	double	hit;
	double	tmp;

	hit = plan->normale.x * (ray->o.x - plan->origin.x);
	hit += plan->normale.y * (ray->o.y - plan->origin.y);
	hit += plan->normale.z * (ray->o.z - plan->origin.z);
	hit += plan->d;
	tmp = plan->normale.x * ray->d.x + plan->normale.y * ray->d.y +
			plan->normale.z * ray->d.z;
	hit /= tmp;
	hit *= -1;
	if (hit < *near && hit > 0)
	{
		*near = hit;
		return (1);
	}
	return (0);
}
