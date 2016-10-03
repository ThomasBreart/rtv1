/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:48:47 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/03 17:29:16 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mlx	*get_mlx(void)
{
	static t_mlx	mlx;

	return (&mlx);
}

t_var	*get_var(void)
{
	static t_var	var;

	return (&var);
}

t_scene	*get_scene(void)
{
	static t_scene	scene;

	return (&scene);
}

void	init(void)
{
	t_var		*var;
	t_scene		*scene;

	var = get_var();
	scene = get_scene();
	var->win_abs = 1000;
	var->win_ord = 1000;
	scene->cam = NULL;
//	var->scene.sphere = NULL;
//	var->scene.sphere_index = 0;
//	var->scene.type_obj[0] = -1;
	scene->obj_index = -1;
}

int		add_cam(char *line)
{
	t_scene		*scene;
	char		**tab;
	char		**tmp;
	double		coords[6];
	int			i;

	scene = get_scene();
	if (scene->cam != NULL)
	{
		ft_putendl_fd("many cameras", STDERR_FILENO);
		return (-1);
	}
	if ((tab = ft_strsplit(line + 4, ',')) == NULL)
	{
		ft_putendl_fd("camera - parse error", STDERR_FILENO);
		return (-1);
	}
	i = 0;
	tmp = tab;
	while (*tmp != NULL)
	{
		if (i >= 6)
		{
			ft_putendl_fd("camera - parse error", STDERR_FILENO);
			return (-1);
		}
		coords[i] = atof(*tmp);
		++tmp;
		++i;
	}
	scene->cam = (t_cam*)malloc(sizeof(t_cam)); //
	scene->cam->origin.x = coords[0];
	scene->cam->origin.y = coords[1];
	scene->cam->origin.z = coords[2];
	scene->cam->dir.x = coords[3];
	scene->cam->dir.y = coords[4];
	scene->cam->dir.z = coords[5];
	free_double_tab(tab);
	return (1);
}

int		is_hexa(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
		return (1);
	return (0);
}

double	convert(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else
		return (c - 'a' + 10);
}

double	ft_atod_h(char *str)
{
	double		nb;

	nb = 0;
	while (ft_isblank(*str))
		str++;
	while (is_hexa(*str))
	{
		nb = nb * 16 + convert(*str);
		++str;
	}
	return (nb);
}

int		parse_hexa(char *str, double *coords)
{
	char	*tmp;
	int		i;
	char	hex[3];

	while (ft_isblank(*str))
		++str;
	tmp = str;
	i = 1;
	while (*tmp != '\0')
	{
		if (i > 8/* || is_hexa(*tmp) == 0*/)// formater les hexas
			return (-1); // msg err
		++i;
		++tmp;
	}
	tmp = str;
	hex[2] = 0;
	hex[0] = *tmp;
	hex[1] = *(tmp + 1);
	coords[0] = ft_atod_h((char*)&hex);
	hex[0] = *(tmp + 2);
	hex[1] = *(tmp + 3);
	coords[1] = ft_atod_h(hex);
	hex[0] = *(tmp + 4);
	hex[1] = *(tmp + 5);
	coords[2] = ft_atod_h(hex);
	return (1);
}

int		add_sphere(char *line)
{
	t_scene		*scene;
	char		**tab;
	char		**tmp;
	int			i;
	double		coords[7];

	scene = get_scene();
	++scene->obj_index;
	if (scene->obj_index > 20)
	{
		ft_putendl_fd("Too much objects bro", STDERR_FILENO);
		return (-1);
	}
	if ((tab = ft_strsplit(line + 7, ',')) == NULL)
	{
		ft_putendl_fd("sphere - parse error", STDERR_FILENO);
		return (-1);
	}
	i = 0;
	tmp = tab;
	while (*tmp != NULL)
	{
		if (i >= 5)
		{
			ft_putendl_fd("sphere - parse error", STDERR_FILENO);
			return (-1);
		}
		if (i == 4)
			parse_hexa(*tmp, (double*)&coords + i);
		else
			coords[i] = atof(*tmp);
		++tmp;
		++i;
	}
	scene->type_obj[scene->obj_index] = SPHERE;
	scene->obj[scene->obj_index] = (t_obj*)malloc(sizeof(t_sphere)); // ///void*
	scene->obj[scene->obj_index]->sphere.origin.x = coords[0];
	scene->obj[scene->obj_index]->sphere.origin.y = coords[1];
	scene->obj[scene->obj_index]->sphere.origin.z = coords[2];
	scene->obj[scene->obj_index]->sphere.radius = coords[3];
	scene->obj[scene->obj_index]->sphere.r = coords[4];
	scene->obj[scene->obj_index]->sphere.g = coords[5];
	scene->obj[scene->obj_index]->sphere.b = coords[6];
	free_double_tab(tab);
	return (1);
}

int		add_plan(char *line)
{
	t_scene		*scene;
	char		**tab;
	char		**tmp;
	int			i;
	double		coords[10];

	scene = get_scene();
	++scene->obj_index;
	if (scene->obj_index > 20)
	{
		ft_putendl_fd("Too much objects bro", STDERR_FILENO);
		return (-1);
	}
	if ((tab = ft_strsplit(line + 5, ',')) == NULL)
	{
		ft_putendl_fd("plan - parse error", STDERR_FILENO);
		return (-1);
	}
	i = 0;
	tmp = tab;
	while (*tmp != NULL)
	{
		if (i >= 8)
		{
			ft_putendl_fd("plan - parse error", STDERR_FILENO);
			return (-1);
		}
		if (i == 7)
			parse_hexa(*tmp, coords + i);
		else
			coords[i] = atof(*tmp);
		++tmp;
		++i;
	}
	scene->type_obj[scene->obj_index] = PLAN;
	scene->obj[scene->obj_index] = (t_obj*)malloc(sizeof(t_plan)); // ///void*
	scene->obj[scene->obj_index]->plan.origin.x = coords[0];
	scene->obj[scene->obj_index]->plan.origin.y = coords[1];
	scene->obj[scene->obj_index]->plan.origin.z = coords[2];
	scene->obj[scene->obj_index]->plan.normale.x = coords[3];
	scene->obj[scene->obj_index]->plan.normale.y = coords[4];
	scene->obj[scene->obj_index]->plan.normale.z = coords[5];
	scene->obj[scene->obj_index]->plan.d = coords[6];
	scene->obj[scene->obj_index]->plan.r = coords[7];
	scene->obj[scene->obj_index]->plan.g = coords[8];
	scene->obj[scene->obj_index]->plan.b = coords[9];
	free_double_tab(tab);
	return (1);
}

int		parse_scene(void)
{
	char	*line;
	int		fd;
	int		ret;

	ret = -1;
	fd = open("scene.txt", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0) // msg err -1
	{
		if (ft_strncmp("cam", line, 3) == 0)
		{
			if ((ret = add_cam(line)) == -1) // msg err -1
			{
				ft_strdel(&line);
				break ;
			}
		}
		else if (ft_strncmp("sphere", line, 6) == 0)
		{
			if ((ret = add_sphere(line)) == -1) // msg err -1
			{
				ft_strdel(&line);
				break ;
			}
		}
		else if (ft_strncmp("plan", line, 4) == 0)
		{
			if ((ret = add_plan(line)) == -1) // msg err -1
			{
				ft_strdel(&line);
				break ;
			}
		}
		ft_strdel(&line);
	}
	close(fd);
	return (ret);
}

void	debug_parser(void)
{
	t_scene		*scene;

	scene = get_scene();
	printf("cam - ox: %f, oy: %f, oz: %f, dx: %f, dy: %f, dz: %f\n", 
			scene->cam->origin.x,
			scene->cam->origin.y,
			scene->cam->origin.z,
			scene->cam->dir.x,
			scene->cam->dir.y,
			scene->cam->dir.z);
	printf("obj1 - type: %d, obj_index: %d, ox: %f, oy: %f, oz: %f, radius: %f, r: %f, g: %f, b: %f\n",
			scene->type_obj[0],
			scene->obj_index,
			scene->obj[0]->sphere.origin.x,
			scene->obj[0]->sphere.origin.y,
			scene->obj[0]->sphere.origin.z,
			scene->obj[0]->sphere.radius,
			scene->obj[0]->sphere.r,
			scene->obj[0]->sphere.g,
			scene->obj[0]->sphere.b);
	printf("obj2 - type: %d, obj_index: %d, ox: %f, oy: %f, oz: %f, radius: %f, r: %f, g: %f, b: %f\n",
			scene->type_obj[1],
			scene->obj_index,
			scene->obj[1]->sphere.origin.x,
			scene->obj[1]->sphere.origin.y,
			scene->obj[1]->sphere.origin.z,
			scene->obj[1]->sphere.radius,
			scene->obj[1]->sphere.r,
			scene->obj[1]->sphere.g,
			scene->obj[1]->sphere.b);
	printf("obj3 - type: %d, obj_index: %d, ox: %f, oy: %f, oz: %f, nx: %f, ny: %f, nz: %f, d: %f, r: %f, g: %f, b: %f\n",
			scene->type_obj[2],
			scene->obj_index,
			scene->obj[2]->plan.origin.x,
			scene->obj[2]->plan.origin.y,
			scene->obj[2]->plan.origin.z,
			scene->obj[2]->plan.normale.x,
			scene->obj[2]->plan.normale.y,
			scene->obj[2]->plan.normale.z,
			scene->obj[2]->plan.d,
			scene->obj[2]->plan.r,
			scene->obj[2]->plan.g,
			scene->obj[2]->plan.b);
}

int		main(void)
{
	init();
	if (parse_scene() == -1)
		return (-1); // penser a free si err
	debug_parser();
	display();
	return (0);
}
