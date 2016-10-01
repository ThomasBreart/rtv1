/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:58:54 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/01 16:05:22 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cam(t_cam *cam, t_var *var)
{
//	double		fov = 1;
/*	t_vec3d		tmp1;
	t_vec3d		tmp2;
	t_vec3d		tmp3;
	t_vec3d		tmp4;
	t_vec3d		tmp5;*/

	cam->origin.x = 0;
	cam->origin.y = 0;
	cam->origin.z = 0;
	cam->dir.x = 0;//
	cam->dir.y = 0;//
	cam->dir.z = 100;
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
/*	printf("lenght upveec: %f\n", sqrt(cam->upvec.x * cam->upvec.x + cam->upvec.y * cam->upvec.y + cam->upvec.z * cam->upvec.z));
	printf("upveec x: %f, y: %f, z: %f\n", cam->upvec.x, cam->upvec.y, cam->upvec.z);
	printf("dirveec x: %f, y: %f, z: %f\n", cam->dirvec.x, cam->dirvec.y, cam->dirvec.z);
	printf("rightveec x: %f, y: %f, z: %f\n", cam->rightvec.x, cam->rightvec.y, cam->rightvec.z);
*/
	cam->viewplane_upleft = vector_init(cam->origin.x, cam->origin.y, cam->origin.z);
//	printf("x: %f, y: %f, z: %f\n", cam->viewplane_upleft.x, cam->viewplane_upleft.y, cam->viewplane_upleft.z);
	cam->viewplane_upleft = vector_add(cam->viewplane_upleft, vector_multiply_real(cam->dirvec, /*cam->dir.z*/ 1));
//	printf("x: %f, y: %f, z: %f\n", cam->viewplane_upleft.x, cam->viewplane_upleft.y, cam->viewplane_upleft.z);
	cam->viewplane_upleft = vector_add(cam->viewplane_upleft, vector_multiply_real(cam->upvec, cam->viewplane_height / 2.0));
//	printf("x: %f, y: %f, z: %f\n", cam->viewplane_upleft.x, cam->viewplane_upleft.y, cam->viewplane_upleft.z);
	cam->viewplane_upleft = vector_sub(cam->viewplane_upleft, vector_multiply_real(cam->rightvec, cam->viewplane_width / 2.0));
//	printf("x: %f, y: %f, z: %f\n", cam->viewplane_upleft.x, cam->viewplane_upleft.y, cam->viewplane_upleft.z);
//	tmp1 = vector_multiply_real(cam->dirvec .....);
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
	var->sphere.origin.x = 2;
	var->sphere.origin.y = 2;
	var->sphere.origin.z = 20;
	var->sphere.radius = 2;
	var->sphere2.origin.x = 0;
	var->sphere2.origin.y = 0;
	var->sphere2.origin.z = 10;
	var->sphere2.radius = 2;
//	init_scene(var);
	//init_light
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, var->win_abs, var->win_ord, "RTV1 - 42");
	mlx_expose_hook(mlx->win, expose_hook, mlx);
	mlx_loop(mlx->mlx);
}
