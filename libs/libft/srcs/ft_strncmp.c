/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:10:18 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/08 21:35:42 by inwagner         ###   ########.fr       */
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
	i = 0;
	while (i < n && cstra[i] && cstrb[i] && cstra[i] == cstrb[i])
		i++;
	return ((int)(cstra[i] - cstrb[i]));
}
