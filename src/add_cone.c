/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 10:19:01 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/16 10:22:30 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	add_cone(char *line)
{
	t_scene		*scene;
	char		**tab;
	double		coords[10];

	scene = get_scene();
	++scene->obj_index;
	if (scene->obj_index > 20)
	{
		ft_putendl_fd("Too much objects bro", STDERR_FILENO);
		exit(-1);
	}
	tab = split_data(line + 5, 8, "cone");
	extract_data(tab, coords, 8, 1);
	scene->obj[scene->obj_index].type = CONE;
	scene->obj[scene->obj_index].origin.x = coords[0];
	scene->obj[scene->obj_index].origin.y = coords[1];
	scene->obj[scene->obj_index].origin.z = coords[2];
	scene->obj[scene->obj_index].normale.x = coords[3];
	scene->obj[scene->obj_index].normale.y = coords[4];
	scene->obj[scene->obj_index].normale.z = coords[5];
	scene->obj[scene->obj_index].radius = coords[6];
	scene->obj[scene->obj_index].r = coords[7];
	scene->obj[scene->obj_index].g = coords[8];
	scene->obj[scene->obj_index].b = coords[9];
	free_double_tab(tab);
	vector_normalize(&scene->obj[scene->obj_index].normale);
}
