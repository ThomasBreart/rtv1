/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 12:06:57 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/16 12:07:04 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	debug_cam(t_cam *cam)
{
	printf("lenght upvec: %f\n", sqrt(cam->upvec.x * cam->upvec.x + cam->upvec.y * cam->upvec.y + cam->upvec.z * cam->upvec.z));
	printf("upvec x: %f, y: %f, z: %f\n", cam->upvec.x, cam->upvec.y, cam->upvec.z);
	printf("dirvec x: %f, y: %f, z: %f\n", cam->dirvec.x, cam->dirvec.y, cam->dirvec.z);
	printf("rightvec x: %f, y: %f, z: %f\n", cam->rightvec.x, cam->rightvec.y, cam->rightvec.z);
	printf("x: %f, y: %f, z: %f\n", cam->viewplane_upleft.x, cam->viewplane_upleft.y, cam->viewplane_upleft.z);
}
