/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:11:45 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 12:28:33 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *str, const char *reject)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (!ft_strchr(reject, *str))
			count++;
		else
			break ;
		str++;
	}
	return (count);
}
