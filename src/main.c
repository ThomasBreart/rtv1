/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 06:48:47 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/01 20:47:49 by tbreart          ###   ########.fr       */
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

void	init(t_var *var)
{
	var->win_abs = 1000;
	var->win_ord = 1000;
	var->scene.cam = NULL;
//	var->scene.sphere = NULL;
//	var->scene.sphere_index = 0;
	var->scene.type_obj = -1;
	var->scene.sphere_index = 0;
}

int		add_cam(char *line)
{
	t_var		*var;
	char		**tab;
	double		coords[6];
	int			i;

	var = get_var();
	if (var->scene.cam != NULL)
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
	while (*tab != NULL)
	{
		if (i > 5)
		{
			ft_putendl_fd("camera - parse error", STDERR_FILENO);
			return (-1);
		}
		coords[i] = atof(*tab);
		++tab;
		++i;
	}
	var->scene.cam = (t_cam*)malloc(sizeof(t_cam)); //
	var->scene.cam->origin.x = coords[0];
	var->scene.cam->origin.y = coords[1];
	var->scene.cam->origin.z = coords[2];
	var->scene.cam->dir.x = coords[3];
	var->scene.cam->dir.y = coords[4];
	var->scene.cam->dir.z = coords[5];
	free_double_tab(tab);
	return (1);
}

int		add_sphere(char *line)
{
	t_var		*var;

	var = get_var();
	if (var->scene.sphere_index > 19)
	{
		ft_putendl_fd("Too much spheres bro", STDERR_FILENO);
		return (-1);
	}
	
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

int		main(void)
{
	t_var	*var;

	var = get_var();
	init(var);
	if (parse_scene() == -1)
		return (-1);
	display();
	return (0);
}
