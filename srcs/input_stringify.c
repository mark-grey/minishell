/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stringify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:18:47 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/17 19:24:48 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_closes(char *str)
{
	char	quote;
	int		paired_quotes;

	if (*str != '\'' && *str != '"')
		return (0);
	quote = *str++;
	paired_quotes = 0;
	while (*str)
		if (*str++ == quote)
			paired_quotes = !paired_quotes;
	return (paired_quotes);
}

static int	count_args(char *args, int single_arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (is_quote(args[i] && quote_closes(&args[i])))
			get_quote(args, &i);
		while (ft_isblank(args[i + 1]))
			args++;
		if (ft_isblank(args[i]) || !args[i + 1])
		{
			if (single_arg && args[i + 1])
				return (i + 1);
			else if (single_arg)
				return (i);
			else
				count++;
		}
		i++;
	}
	return (count);
}

static char	*strlcpy_quoted(char *args, int len)
{
	char	*str;
	int		i;
	int		has_quote;

	i = -1;
	has_quote = 0;
	while (++i < len -1 && !has_quote)
		if (is_quote(args[i]) && quote_closes(&args[i]))
			has_quote = (int)args[i];
	if (has_quote)
		len -= 2;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		if (*args != (char)has_quote)
			str[i++] = *args;
		args++;
	}
	str[i] = '\0';
	return (str);
}

static char	*set_arg(char *args, char **pointer)
{
	char		*str;
	int			len;
	int			start;
	static int	new_arg;

	start = new_arg;
	len = count_args(&args[start], 1);
	new_arg += len + 1;
	while (ft_isblank(args[new_arg]))
		new_arg++;
	if (!args[new_arg])
	{
		len++;
		new_arg = 0;
	}
	str = strlcpy_quoted(&args[start], len + 1);
	if (!str)
	{
		clear_ptr_array(pointer);
		exit_program(OUT_OF_MEMORY);
	}
	return (str);
}

char	**stringify_args(char *args)
{
	int		i;
	int		count;
	char	**pointers;

	if (!args)
		return (NULL);
	i = 0;
	count = count_args(args, 0);
	pointers = malloc(sizeof(char *) * (count + 1));
	if (!pointers)
		exit_program(OUT_OF_MEMORY);
	while (i <= count)
		pointers[i++] = NULL;
	i = 0;
	while (i < count)
		pointers[i++] = set_arg(args, pointers);
	return (pointers);
}
