/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:58:54 by tbreart           #+#    #+#             */
/*   Updated: 2016/09/30 22:39:19 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cam(t_cam *cam, t_var *var)
{
	double		fov = 1;

	cam->origin.x = 0;
	cam->origin.y = 0;
	cam->origin.z = 0;
	cam->dir.x = 0;
	cam->dir.y = 0;
	cam->dir.z = fov;
	cam->viewplane_height = 10;
	cam->viewplane_width = 10;
	cam->xindent = cam->viewplane_width / (double)var->win_abs;
	cam->yindent = cam->viewplane_height / (double)var->win_ord;

	cam->dirvec = vector_sub(cam->dir, cam->origin);
	cam->upvec = vector_init(0, 1, 0);
	cam->rightvec = cross_product(cam->upvec, cam->dirvec); ///
	cam->upvec = cross_product(cam->dirvec, cam->rightvec); ///
	vector_normalize(&cam->dirvec);
	vector_normalize(&cam->upvec);
	vector_normalize(&cam->rightvec);
	printf("upveec x: %f, y: %f, z: %f\n", cam->upvec.x, cam->upvec.y, cam->upvec.z);
	printf("dirveec x: %f, y: %f, z: %f\n", cam->dirvec.x, cam->dirvec.y, cam->dirvec.z);
	printf("rightveec x: %f, y: %f, z: %f\n", cam->rightvec.x, cam->rightvec.y, cam->rightvec.z);

	cam->viewplane_upleft = vector_init(cam->origin.x, cam->origin.y, cam->origin.z);
	printf("x: %f, y: %f, z: %f\n", cam->viewplane_upleft.x, cam->viewplane_upleft.y, cam->viewplane_upleft.z);
	cam->viewplane_upleft = vector_add(cam->viewplane_upleft, vector_multiply_real(cam->dirvec, cam->dir.z));
	printf("x: %f, y: %f, z: %f\n", cam->viewplane_upleft.x, cam->viewplane_upleft.y, cam->viewplane_upleft.z);
	cam->viewplane_upleft = vector_add(cam->viewplane_upleft, vector_multiply_real(cam->upvec, cam->viewplane_height / 2.0));
	printf("x: %f, y: %f, z: %f\n", cam->viewplane_upleft.x, cam->viewplane_upleft.y, cam->viewplane_upleft.z);
	cam->viewplane_upleft = vector_sub(cam->viewplane_upleft, vector_multiply_real(cam->rightvec, cam->viewplane_width / 2.0));
	printf("x: %f, y: %f, z: %f\n", cam->viewplane_upleft.x, cam->viewplane_upleft.y, cam->viewplane_upleft.z);
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
	init_cam(&var->cam, var);
	var->sphere.origin.x = 200;
	var->sphere.origin.y = 200;
	var->sphere.origin.z = 100;
	var->sphere.radius = 40;
//	init_scene(var);
	//init_light
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, var->win_abs, var->win_ord, "RTV1 - 42");
	mlx_expose_hook(mlx->win, expose_hook, mlx);
	mlx_loop(mlx->mlx);
}
