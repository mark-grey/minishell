/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:09:35 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/08 19:39:05 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	ldst;
	size_t	lsrc;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (len <= ldst)
		return (len + lsrc);
	i = 0;
	while (ldst + i != len - 1 && src[i++])
		dst[ldst + i] = src[i];
	dst[ldst + i] = 0;
	return (ldst + lsrc);
}
