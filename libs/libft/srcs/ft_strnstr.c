/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:08:30 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/08 21:53:10 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	l_little;

	if (!*little)
		return ((char *)big);
	l_little = ft_strlen(little);
	while (*big && l_little <= n-- && ft_strncmp(big, little, l_little))
		big++;
	if (!ft_strncmp(big, little, l_little))
		return ((char *)big);
	return (0);
}
