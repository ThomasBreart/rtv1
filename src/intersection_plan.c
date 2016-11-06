/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:50:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/06 12:35:21 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		intersection_plan(t_obj *plan, t_ray *ray)
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
	tmp = hit;
	hit = round(hit * 1000000000) / 1000000000; // ??
	if (hit < ray->lenght && hit > 0)
	{
		ray->lenght = hit;
		return (1);
	}
	return (0);
}
