/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:51:30 by tbreart           #+#    #+#             */
/*   Updated: 2016/09/30 21:01:04 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RTV1_H
# define FT_RTV1_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
#include <stdio.h>

typedef	struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img_ptr;
	int				bpp;
	char			*data;
	int				sizeline;
}					t_mlx;

typedef struct		s_vec3d
{
	double			x;
	double			y;
	double			z;
}					t_vec3d;

typedef struct		s_ray
{
	t_vec3d			o;
	t_vec3d			d;
}					t_ray;

typedef struct		s_sphere
{
	t_vec3d			origin;
	double			radius;
}					t_sphere;

typedef struct		s_cam
{
	t_vec3d			origin;
	t_vec3d			dir;
	t_vec3d			dirvec;
	t_vec3d			upvec;
	t_vec3d			rightvec;
	t_vec3d			viewplane_upleft;
	double			viewplane_height;
	double			viewplane_width;
	double			xindent;
	double			yindent;
}					t_cam;

typedef	struct		s_var
{
	int				win_abs;
	int				win_ord;
	double			cam_dir;
	t_sphere		sphere;
	t_cam			cam;
}					t_var;

void				display(void);
int					expose_hook(t_mlx *mlx);
t_mlx				*get_mlx(void);
t_var				*get_var(void);
t_vec3d				*vector_copy(t_vec3d *a);
double				vector_dot(t_vec3d *a, t_vec3d *b);
void				vector_normalize(t_vec3d *v);
t_vec3d				vector_sub(t_vec3d a, t_vec3d b);
t_vec3d				vector_add(t_vec3d a, t_vec3d b);
t_vec3d				vector_init(double x, double y, double z);
t_vec3d				cross_product(t_vec3d a, t_vec3d b);
t_vec3d				vector_multiply_real(t_vec3d a, double b);
double				ft_carre(double x);
#endif
