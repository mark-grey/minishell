/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:13:56 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/19 21:41:59 by maalexan         ###   ########.fr       */
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

/*
**	Verifies if the received string has
**	unclosed quotes, to enable adequate
**	treatment as necessary
**/
int	quote_closes(char *str)
{
	char	quote;

	if (*str != '\'' && *str != '"')
		return (0);
	quote = *str++;
	while (*str && *str != quote)
		str++;
	return (*str == quote);
}

/*
**	Guarantees the string
**	has only one quote
**/
int	has_single_quote(char *str)
{
	int	quote;

	quote = 0;
	while (*str)
		if (is_quote(*str++))
			quote++;
	if (quote == 1)
		return (1);
	return (0);
}

/*
**	Confirms that the string is an
**	environment variable and that
**	it has only one quote
**/
int	is_a_quoted_var(char *str)
{
	t_ctrl	*ctrl;
	t_env	*var;

	ctrl = get_control();
	var = search_var(str, ctrl->env);
	if (!var || !has_single_quote(var->value))
		return (0);
	return (1);
}