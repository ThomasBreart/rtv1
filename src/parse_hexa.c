/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 01:18:43 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/21 01:18:59 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	parse_hexa_error(char *tmp)
{
	int		i;

	i = 1;
	while (*tmp != '\0')
	{
		if ((i < 7 && is_hexa(*tmp) == 0) || i > 8)
		{
			ft_putendl_fd("bad hexa number", STDERR_FILENO);
			exit(-1);
		}
		++i;
		++tmp;
	}
}

int				parse_hexa(char *str, double *coords)
{
	char	hex[3];

	while (ft_isblank(*str))
		++str;
	parse_hexa_error(str);
	hex[2] = 0;
	hex[0] = *str;
	hex[1] = *(str + 1);
	coords[0] = ft_atod_h((char*)&hex);
	hex[0] = *(str + 2);
	hex[1] = *(str + 3);
	coords[1] = ft_atod_h(hex);
	hex[0] = *(str + 4);
	hex[1] = *(str + 5);
	coords[2] = ft_atod_h(hex);
	return (1);
}
