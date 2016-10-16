/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 11:38:39 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/16 12:01:30 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	img_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	memcpy(mlx->data + (y * mlx->sizeline) + ((mlx->bpp / 8) * x), &color, 3);
}
