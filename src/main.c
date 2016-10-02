/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:48:47 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/02 14:25:46 by tbreart          ###   ########.fr       */
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
	scene->obj_index = 0;
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

int		add_sphere(char *line)
{
	t_scene		*scene;
	char		**tab;
	char		**tmp;
	int			i;
	double		coords[4];

	scene = get_scene();
	if (scene->obj_index > 19)
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
		if (i >= 4)
		{
			ft_putendl_fd("sphere - parse error", STDERR_FILENO);
			return (-1);
		}
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
	++scene->obj_index;
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
			if ((ret = add_sphere(line)) == -1) // msg err -1
			{
				ft_strdel(&line);
				break ;
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
	printf("obj1 - type: %d, obj_index: %d, ox: %f, oy: %f, oz: %f, radius: %f\n", 
			scene->type_obj[0],
			scene->obj_index,
			scene->obj[0]->sphere.origin.x,
			scene->obj[0]->sphere.origin.y,
			scene->obj[0]->sphere.origin.z,
			scene->obj[0]->sphere.radius);
	printf("obj2 - type: %d, obj_index: %d, ox: %f, oy: %f, oz: %f, radius: %f\n", 
			scene->type_obj[1],
			scene->obj_index,
			scene->obj[1]->sphere.origin.x,
			scene->obj[1]->sphere.origin.y,
			scene->obj[1]->sphere.origin.z,
			scene->obj[1]->sphere.radius);
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
