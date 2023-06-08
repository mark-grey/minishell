/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:08:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/08 17:41:02 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int c, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)src;
	i = 0;
	if (n)
		while (i++ < n)
			str[i] = (unsigned char)c;
	return (src);
}
