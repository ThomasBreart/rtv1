/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 01:17:20 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 18:51:04 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parser_error(char *error)
{
	ft_putendl_fd(error, STDERR_FILENO);
	exit(-1);
}

char		**split_data(char *str, int max_data, char *object_name)
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

static void	check_only_numbers(char *str, char *strtmp, int last_number)
{
	int		end;
	int		minus;
	int		coma;

	coma = 0;
	minus = 0;
	end = 0;
	if (*str == ' ')
		++str;
	while (*str != '\0')
	{
		if (*str == '-' && minus == 0)
			minus = 1;
		else if (*str == '.' && coma == 0)
			coma = 1;
		else if (*str == ')' && end == 0 && last_number == 1)
			end = 1;
		else if (ft_isdigit(*str) == 0)
		{
			ft_putstr_fd("number bad formated: ", STDERR_FILENO);
			ft_putendl_fd(strtmp, STDERR_FILENO);
			exit(-1);
		}
		++str;
	}
}

void		extract_data(char **tab, double *coords, int max_data,
																char last_hexa)
{
	int		i;
	int		last_number;
	char	**tmp;

	i = 0;
	while (*tab != NULL)
	{
		last_number = 0;
		if (last_hexa == 1 && i == (max_data - 1))
			parse_hexa(*tab, coords + i);
		else
		{
			tmp = tab;
			++tmp;
			if (last_hexa == 0 && *tmp == NULL)
				last_number = 1;
			check_only_numbers(*tab, *tab, last_number);
			coords[i] = atof(*tab);
		}
		++tab;
		++i;
	}
}
