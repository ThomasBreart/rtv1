/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:29:05 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/05 22:29:14 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	add_cam(char *line)
{
	t_scene		*scene;
	char		**tab;
	double		coords[6];

	scene = get_scene();
	if (scene->cam.init != 0)
	{
		ft_putendl_fd("many cameras", STDERR_FILENO);
		exit(-1);
	}
	tab = split_data(line + 4, 6, "camera");
	extract_data(tab, coords, 6, 0);
	scene->cam.origin.x = coords[0];
	scene->cam.origin.y = coords[1];
	scene->cam.origin.z = coords[2];
	scene->cam.dir.x = coords[3];
	scene->cam.dir.y = coords[4];
	scene->cam.dir.z = coords[5];
	scene->cam.init = 1;
	free_double_tab(tab);
}
