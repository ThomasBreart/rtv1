/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:48:47 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/05 22:36:17 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init(void)
{
	t_var		*var;
	t_scene		*scene;

	var = get_var();
	scene = get_scene();
	var->win_abs = 1000;
	var->win_ord = 1000;
	scene->cam.init = 0;
	scene->obj_index = -1;
}

void	debug_parser(void)
{
	t_scene		*scene;

	scene = get_scene();
	printf("cam - ox: %f, oy: %f, oz: %f, dx: %f, dy: %f, dz: %f\n", 
			scene->cam.origin.x,
			scene->cam.origin.y,
			scene->cam.origin.z,
			scene->cam.dir.x,
			scene->cam.dir.y,
			scene->cam.dir.z);
	printf("obj1 - type: %d, obj_index: %d, ox: %f, oy: %f, oz: %f, radius: %f, r: %f, g: %f, b: %f\n",
			scene->obj[0].type,
			scene->obj_index,
			scene->obj[0].origin.x,
			scene->obj[0].origin.y,
			scene->obj[0].origin.z,
			scene->obj[0].radius,
			scene->obj[0].r,
			scene->obj[0].g,
			scene->obj[0].b);
	printf("obj2 - type: %d, obj_index: %d, ox: %f, oy: %f, oz: %f, radius: %f, r: %f, g: %f, b: %f\n",
			scene->obj[0].type,
			scene->obj_index,
			scene->obj[1].origin.x,
			scene->obj[1].origin.y,
			scene->obj[1].origin.z,
			scene->obj[1].radius,
			scene->obj[1].r,
			scene->obj[1].g,
			scene->obj[1].b);
	printf("obj3 - type: %d, obj_index: %d, ox: %f, oy: %f, oz: %f, nx: %f, ny: %f, nz: %f, d: %f, r: %f, g: %f, b: %f\n",
			scene->obj[0].type,
			scene->obj_index,
			scene->obj[2].origin.x,
			scene->obj[2].origin.y,
			scene->obj[2].origin.z,
			scene->obj[2].normale.x,
			scene->obj[2].normale.y,
			scene->obj[2].normale.z,
			scene->obj[2].d,
			scene->obj[2].r,
			scene->obj[2].g,
			scene->obj[2].b);
}

int		main(void)
{
	init();
	if (parse_scene() == -1)
		return (-1); // penser a free si err
	debug_parser();
	display();
	return (0);
}
