/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:07:11 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/08 18:45:41 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*dst;

	if (!num || !size || num * size / size != num)
		return (NULL);
	dst = malloc(num * size);
	if (!dst)
		return (NULL);
	ft_bzero(dst, num * size);
	return (dst);
}
