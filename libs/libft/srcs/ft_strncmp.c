/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:10:18 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 11:31:51 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *stra, const char *strb, size_t n)
{
	size_t			i;
	unsigned char	*cstra;
	unsigned char	*cstrb;

	if (!stra || !strb || !n)
		return (0);
	cstra = (unsigned char *)stra;
	cstrb = (unsigned char *)strb;
	i = -1;
	while (++i != n)
		if (cstra[i] != cstrb[i])
			return ((int)(cstra[i] - cstrb[i]));
	return (0);
}
