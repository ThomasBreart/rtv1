/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:27:26 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/15 09:40:11 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	add_light(char *line)
{
	t_scene		*scene;
	char		**tab;
	double		coords[6];

	scene = get_scene();
	++scene->light_index;
	if (scene->light_index > 20)
	{
		ft_putendl_fd("Too much lights bro", STDERR_FILENO);
		exit(-1);
	}
	tab = split_data(line + 6, 4, "light");
	extract_data(tab, coords, 4, 1);
	scene->light[scene->light_index].type = OMNI_LIGHT;
	scene->light[scene->light_index].origin.x = coords[0];
	scene->light[scene->light_index].origin.y = coords[1];
	scene->light[scene->light_index].origin.z = coords[2];
	scene->light[scene->light_index].r = coords[3];
	scene->light[scene->light_index].g = coords[4];
	scene->light[scene->light_index].b = coords[5];
	free_double_tab(tab);
}
