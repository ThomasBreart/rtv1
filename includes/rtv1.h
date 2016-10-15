/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:51:30 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/15 09:40:40 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RTV1_H
# define FT_RTV1_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
#include <stdio.h>
#include "../libft/includes/libft.h"

# define SPHERE 1
# define PLAN 2

# define OMNI_LIGHT 100

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

typedef	struct		s_obj
{
	int				type;
	t_vec3d			origin;
	t_vec3d			normale;
	double			radius;
	double			d;
	double			r;
	double			g;
	double			b;
}					t_obj;
/*
typedef struct		s_sphere
{
	t_vec3d			origin;
	double			radius;
	double			r;
	double			g;
	double			b;
	//double			color;
}					t_sphere;

typedef struct		s_plan
{
	t_vec3d			origin;
	t_vec3d			normale;
	double			d;
	double			r;
	double			g;
	double			b;
	//double			color;
}					t_plan;
*/
typedef struct		s_cam
{
	t_vec3d			origin;
	t_vec3d			dir;
	t_vec3d			dirvec;
	t_vec3d			upvec;
	t_vec3d			rightvec;
	t_vec3d			viewplane_upleft;
	char			init;
	double			viewplane_height;
	double			viewplane_width;
	double			xindent;
	double			yindent;
}					t_cam;

typedef	struct		s_light
{
	int				type;
	t_vec3d			origin;
	double			r;
	double			g;
	double			b;
}					t_light;

typedef	struct		s_scene
{
	t_cam			cam;
//	int				type_obj[20];
	t_obj			obj[20];
	t_light			light[20];
	int				obj_index;
	int				light_index;
}					t_scene;

typedef	struct		s_near
{
	double			lenght;
//	int				type_obj;
	t_obj			*obj;
}					t_near;

typedef	struct		s_var
{
	int				win_abs;
	int				win_ord;
	double			cam_dir;
}					t_var;

void				add_cam(char *line);
void				add_light(char *line);
void				add_plan(char *line);
void				add_sphere(char *line);
void				display(void);
int					expose_hook(t_mlx *mlx);
void				extract_data(char **tab, double *coords, int max_data, char last_hexa);
double				ft_atod_h(char *str);
t_mlx				*get_mlx(void);
t_var				*get_var(void);
t_scene				*get_scene(void);
int					intersection_plan(t_obj *plan, t_ray *ray, double *near);
int					intersection_sphere(t_obj *sphere, t_ray *ray, double *near);
int					parse_scene(void);
char				**split_data(char *str, int max_data, char *object_name);
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
