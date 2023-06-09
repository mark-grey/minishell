/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:08:20 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/08 21:37:32 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	size_t	i;

	if (!c)
		return ((char *)&src[ft_strlen(src)]);
	i = 0;
	while (src[i] && src[i] != (char)(c))
		i++;
	return ((char *)&src[i]);
}
