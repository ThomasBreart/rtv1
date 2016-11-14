/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:48:47 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 20:07:12 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init(void)
{
	t_var		*var;
	t_scene		*scene;
	t_mlx		*mlx;

	var = get_var();
	scene = get_scene();
	mlx = get_mlx();
	var->win_abs = 640;
	var->win_ord = 480;
	scene->cam.init = 0;
	scene->obj_index = -1;
	scene->light_index = -1;
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->img_ptr = NULL;
	mlx->bpp = -1;
	mlx->data = NULL;
	mlx->sizeline = -1;
}

int		main(int argc, char **argv)
{
	if (argc > 2)
	{
		ft_putendl_fd("Too many arguments", STDERR_FILENO);
		return (-1);
	}
	init();
	if (parse_scene(argv[1]) == -1)
		return (-1);
	display();
	return (0);
}
