/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:24:45 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/05 23:09:16 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

char	**split_data(char *str, int max_data, char *object_name)
{
	char	**tab;

	if ((tab = ft_strsplit(str, ',')) == NULL)
	{
		ft_putstr_fd(object_name, STDERR_FILENO);
		ft_putendl_fd(" - parse error", STDERR_FILENO);
		exit(-1);
	}
	if (ft_tablen(tab) > max_data)
	{
		ft_putstr_fd(object_name, STDERR_FILENO);
		ft_putendl_fd(" - parse error", STDERR_FILENO);
		exit(-1);
	}
	return (tab);
}

void	extract_data(char **tab, double *coords, int max_data, char last_hexa)
{
	int		i;

	i = 0;
	while (*tab != NULL)
	{
		if (last_hexa == 1 && i == (max_data - 1))
			parse_hexa(*tab, coords + i); //&coord
		else
			coords[i] = atof(*tab);
		++tab;
		++i;
	}
}

int		parse_scene(void)
{
	char	*line;
	int		fd;
	int		ret;

	ret = -1;
	fd = open("scene.txt", O_RDONLY); // msg err -1
	while ((ret = get_next_line(fd, &line)) > 0) // msg err -1
	{
		if (ft_strncmp("cam", line, 3) == 0)
			add_cam(line);
		else if (ft_strncmp("sphere", line, 6) == 0)
			add_sphere(line);
		else if (ft_strncmp("plan", line, 4) == 0)
			add_plan(line);
		ft_strdel(&line);
	}
	close(fd);
	return (ret);
}
