/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:58:54 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/05 22:37:16 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cam(t_cam *cam, t_var *var)
{
	cam->viewplane_height = 0.5;
	cam->viewplane_width = 0.5;
	cam->xindent = cam->viewplane_width / (double)var->win_abs;
	cam->yindent = cam->viewplane_height / (double)var->win_ord;

	cam->dirvec = vector_sub(cam->dir, cam->origin);
	vector_normalize(&cam->dirvec);
	cam->upvec = vector_init(0, 1, 0);
	cam->rightvec = cross_product(cam->upvec, cam->dirvec); ///
	cam->upvec = cross_product(cam->dirvec, cam->rightvec); ///
	vector_normalize(&cam->dirvec);
	vector_normalize(&cam->upvec);
	vector_normalize(&cam->rightvec);
	cam->viewplane_upleft = vector_init(cam->origin.x, cam->origin.y, cam->origin.z);
	cam->viewplane_upleft = vector_add(cam->viewplane_upleft, vector_multiply_real(cam->dirvec, 1));
	cam->viewplane_upleft = vector_add(cam->viewplane_upleft, vector_multiply_real(cam->upvec, cam->viewplane_height / 2.0));
	cam->viewplane_upleft = vector_sub(cam->viewplane_upleft, vector_multiply_real(cam->rightvec, cam->viewplane_width / 2.0));
}

void	debug_cam(t_cam *cam)
{
	printf("lenght upvec: %f\n", sqrt(cam->upvec.x * cam->upvec.x + cam->upvec.y * cam->upvec.y + cam->upvec.z * cam->upvec.z));
	printf("upvec x: %f, y: %f, z: %f\n", cam->upvec.x, cam->upvec.y, cam->upvec.z);
	printf("dirvec x: %f, y: %f, z: %f\n", cam->dirvec.x, cam->dirvec.y, cam->dirvec.z);
	printf("rightvec x: %f, y: %f, z: %f\n", cam->rightvec.x, cam->rightvec.y, cam->rightvec.z);
	printf("x: %f, y: %f, z: %f\n", cam->viewplane_upleft.x, cam->viewplane_upleft.y, cam->viewplane_upleft.z);
}

void	display(void)
{
	t_mlx	*mlx;
	t_var	*var;
	t_scene		*scene;

	mlx = get_mlx();
	var = get_var();
	scene = get_scene();
	init_cam(&scene->cam, var);
	//debug_cam(scene->cam);
	//init_light
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, var->win_abs, var->win_ord, "RTV1 - 42");
	mlx_expose_hook(mlx->win, expose_hook, mlx);
	mlx_loop(mlx->mlx);
}
