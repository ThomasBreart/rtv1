/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 01:17:20 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/21 01:24:58 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parser_error(char *error)
{
	ft_putendl_fd(error, STDERR_FILENO);
	exit(-1);
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
			parse_hexa(*tab, coords + i);
		else
			coords[i] = atof(*tab);
		++tab;
		++i;
	}
}
