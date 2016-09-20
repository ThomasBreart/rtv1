/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:58:54 by tbreart           #+#    #+#             */
/*   Updated: 2016/09/20 08:49:05 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cam(t_var *var)
{
	double		fov = 30;

	var->cam_o.x = 0;
	var->cam_o.y = 0;
	var->cam_o.z = 0;
//	var->cam_d_x = 0;
//	var->cam_d_y = 0;
	var->cam_d_z = fov;
	
	var->sphere.position.x = 0;
	var->sphere.position.y = 0;
	var->sphere.position.z = 200;
	var->sphere.radius = 40;
}
/*
void	init_scene(t_var *var)
{

}
*/
void	display(void)
{
	t_mlx	*mlx;
	t_var	*var;

	mlx = get_mlx();
	var = get_var();
	init_cam(var);
//	init_scene(var);
	//init_light
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, var->win_abs, var->win_ord, "RTV1 - 42");
	mlx_expose_hook(mlx->win, expose_hook, mlx);
	mlx_loop(mlx->mlx);
}
