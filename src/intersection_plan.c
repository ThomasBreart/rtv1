/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:50:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 17:17:09 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	ceil(hit * 1000000000) / 1000000000;
*/

int		intersection_plan(t_obj *plan, t_ray *ray)
{
	double	hit;

	hit = (((plan->normale.x * (ray->o.x - plan->origin.x)) +
			(plan->normale.y * (ray->o.y - plan->origin.y)) +
			(plan->normale.z * (ray->o.z - plan->origin.z)) +
			plan->d) /
			(plan->normale.x * ray->d.x +
			plan->normale.y * ray->d.y +
			plan->normale.z * ray->d.z)) * -1;
	if (hit < ray->lenght && hit > 0)
	{
		ray->lenght = hit;
		return (1);
	}
	return (0);
}
