/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:58:54 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/16 12:13:02 by tbreart          ###   ########.fr       */
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
	cam->rightvec = cross_product(cam->upvec, cam->dirvec);
	cam->upvec = cross_product(cam->dirvec, cam->rightvec);
	vector_normalize(&cam->upvec);
	vector_normalize(&cam->rightvec);
	cam->viewplane_upleft = vector_init(cam->origin.x, cam->origin.y,
															cam->origin.z);
	cam->viewplane_upleft = vector_add(cam->viewplane_upleft,
										vector_multiply_real(cam->dirvec, 1));
	cam->viewplane_upleft = vector_add(cam->viewplane_upleft,
				vector_multiply_real(cam->upvec, cam->viewplane_height / 2.0));
	cam->viewplane_upleft = vector_sub(cam->viewplane_upleft,
			vector_multiply_real(cam->rightvec, cam->viewplane_width / 2.0));
}

void	prepare_draw(t_mlx *mlx)
{
	int		endian;
	t_var	*var;

	var = get_var();
//	mlx_clear_window(mlx->mlx, mlx->win);///
	if (mlx->img_ptr != NULL)///
		mlx_destroy_image(mlx->mlx, mlx->img_ptr);///
	mlx->img_ptr = mlx_new_image(mlx->mlx, var->win_abs, var->win_ord);
	mlx->data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp, &mlx->sizeline, &endian);
}

void	display(void)
{
	t_mlx		*mlx;
	t_var		*var;
	t_scene		*scene;

	mlx = get_mlx();
	var = get_var();
	scene = get_scene();
	init_cam(&scene->cam, var);
//	debug_cam(&scene->cam);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, var->win_abs, var->win_ord, "RTV1 - 42");
	mlx_expose_hook(mlx->win, expose_hook, mlx);
	mlx_key_hook(mlx->win, key_hook, NULL);
	prepare_draw(mlx);
	raytracer(mlx);
	mlx_loop(mlx->mlx);
}
