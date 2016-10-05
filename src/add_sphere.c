/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:27:26 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/05 22:30:19 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	add_sphere(char *line)
{
	t_scene		*scene;
	char		**tab;
	double		coords[7];

	scene = get_scene();
	++scene->obj_index;
	if (scene->obj_index > 20)
	{
		ft_putendl_fd("Too much objects bro", STDERR_FILENO);
		exit(-1);
	}
	tab = split_data(line + 7, 5, "sphere");
	extract_data(tab, coords, 5, 1);
	scene->obj[scene->obj_index].type = SPHERE;
	scene->obj[scene->obj_index].origin.x = coords[0];
	scene->obj[scene->obj_index].origin.y = coords[1];
	scene->obj[scene->obj_index].origin.z = coords[2];
	scene->obj[scene->obj_index].radius = coords[3];
	scene->obj[scene->obj_index].r = coords[4];
	scene->obj[scene->obj_index].g = coords[5];
	scene->obj[scene->obj_index].b = coords[6];
	free_double_tab(tab);
}
