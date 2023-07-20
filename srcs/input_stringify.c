/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stringify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:18:47 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/19 21:52:00 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static char	*expand_variable(char *src)
{
	t_ctrl	*ctrl;
	t_env	*var;
	char	*str;
	int		len;

	ctrl = get_control();
	var = search_var(src, ctrl->env);
	len = ft_strlen(var->value) + 1;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, var->value, len);
	return (str);
}*/

int	goto_next_quote(char *args)
{
	int		i;
	char	quote;

	i = 1;
	if (!quote_closes(args))
		return (1);
	quote = *args++;
	while (*args++ != quote)
		i++;
	return (i + 1);
}

int	count_args(char *args)
{
	int	count;

	count = 0;
	while (ft_isblank(*args))
		args++;
	while (*args)
	{
		if (is_quote(*args))
			args += goto_next_quote(args);
		else
			args++;
		if (ft_isblank(*args) || !*args)
			count++;
		while (ft_isblank(*args))
			args++;
	}
	return (count);
}

char	**stringify_args(char *args)
{
	char	**pointers;
	int		size;
printf("Im receiving %s\n", args);
	pointers = NULL;
	if (!args)
		return (NULL);
	size = count_args(args);
	printf ("size is %i\n", size);
	exit_program(1);
	return (pointers);
}





























/*
static int	count_args(char *args, int single_arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (is_quote(args[i]) && quote_closes(&args[i]))
			get_quote(args, &i);
		while (ft_isblank(args[i + 1]))
			i++;
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
	printf("args: %i\n", count);
	return (count);
}

static char	*strlcpy_quoted(char *args, int len)
{
	char	*str;
	int		i;
	int		has_quote;

	if (*args == '$' && is_a_quoted_var(args + 1))
		return (expand_variable(args + 1));
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
	new_arg = 0;
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
	print_args(pointers);
	return (pointers);
}


export pog="oi'io" bog='mi"im'

static void	print_args(char **args)
{
	int	i = 0;

	while (*args)
	{
		printf ("arg %i\n", ++i);
		ft_putstr_fd(*args++, STDOUT_FILENO);
		//if (*args)
		//	ft_putstr_fd(" ", STDOUT_FILENO);
		write (1, "\n", STDOUT_FILENO);
	}
}
*/