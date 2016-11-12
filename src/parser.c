/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:24:45 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 18:20:02 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	add_obj(char *line)
{
	if (ft_strncmp("cam", line, 3) == 0 && line[3] == '(')
		add_cam(line);
	else if (ft_strncmp("sphere", line, 6) == 0 && line[6] == '(')
		add_sphere(line);
	else if (ft_strncmp("plan", line, 4) == 0 && line[4] == '(')
		add_plan(line);
	else if (ft_strncmp("light", line, 5) == 0 && line[5] == '(')
		add_light(line);
	else if (ft_strncmp("cylinder", line, 8) == 0 && line[8] == '(')
		add_cylinder(line);
	else if (ft_strncmp("cone", line, 4) == 0 && line[4] == '(')
		add_cone(line);
	else
	{
		if (ft_strlen(line) == 0)
			ft_putendl_fd("empty line", STDERR_FILENO);
		else
			ft_putendl_fd("object bad formated", STDERR_FILENO);
		exit(0);
	}
}

int				parse_scene(char *file)
{
	char	*line;
	int		fd;
	int		ret;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putendl_fd("can't open file", STDERR_FILENO);
		return (-1);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		add_obj(line);
		ft_strdel(&line);
	}
	close(fd);
	if (ret == -1)
		ft_putendl_fd("can't read file", STDERR_FILENO);
	return (ret);
}
