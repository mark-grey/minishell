/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:13:56 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/18 22:58:43 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Bash variable names can only have alpha numeric 
**	characters or an underscore "_" but there is a 
**	special variable "$?" that must be treated
*/
int	valid_var_name(char c)
{
	return (c == '?' || ft_isalnum(c) || c == '_');
}

/*
**	Checks if an environment variable has quotes
**	within it's composition, so they can be expanded
**	AFTER being tokenized
*/
char	*var_has_quote(t_env *env_var)
{
	char	*cursor;

	cursor = env_var->value;
	while (*cursor)
		if (is_quote(*cursor++))
			return (env_var->key);
	return (env_var->value);
}
