/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:51:30 by tbreart           #+#    #+#             */
/*   Updated: 2016/09/20 08:30:23 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RTV1_H
# define FT_RTV1_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>

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
	t_vec3d			position;
	double			radius;
}					t_sphere;

typedef	struct		s_var
{
	int				win_abs;
	int				win_ord;
	t_vec3d			cam_o;
	double			cam_d_x;
	double			cam_d_y;
	double			cam_d_z;
	double			cam_dir;
	t_sphere		sphere;
}					t_var;

void				display(void);
int					expose_hook(t_mlx *mlx);
t_mlx				*get_mlx(void);
t_var				*get_var(void);
t_vec3d				*vector_copy(t_vec3d *a);
double				vector_dot(t_vec3d *a, t_vec3d *b);
void				vector_normalize(t_vec3d *v);
t_vec3d				*vector_sub(t_vec3d *a, t_vec3d *b);
#endif
