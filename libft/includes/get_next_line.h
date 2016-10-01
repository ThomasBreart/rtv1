/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/17 11:04:25 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/01 16:39:50 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 8

# include "libft.h"

typedef	struct	s_var_gnl
{
	int			read_end;
	size_t		j;
	int			a;
	int			ok;
}				t_var_gnl;

int				get_next_line(int const fd, char **line);
#endif
