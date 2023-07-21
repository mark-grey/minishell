/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stringify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:18:47 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/21 18:01:28 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printargs(char **args)
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
		return (0);
	quote = *args++;
	while (*args++ != quote)
		i++;
	return (i);
}

int	size_minus_quotes(char *arg, int len)
{
	int	i;
	int temp;

	i = 0;
	while (i < len)
	{
		temp = 0;
		if (is_quote(arg[i]))
			temp += goto_next_quote(&arg[i]);
		if (temp)
		{
			i += temp;
			len -= 2;
		}
		i++;
	}
	return (i);
}

static char *copy_argument(char *arg, int len)
{
	char	*str;
	int		i;
	int		copychars;

	len = size_minus_quotes(arg, len);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	printf("my len should be %i\n", len);
	while (i < len)
	{
		copychars = 0;
		if (is_quote(*arg))
			copychars += goto_next_quote(arg);
		if (copychars)
		{
			printf("copychars triggered on %s and with value of %i\n", arg, copychars);
			ft_memcpy(&str[i], arg + 1, copychars - 1);
			arg += copychars + 1;
			i += copychars - 1;
		}
		else
			str[i++] = *arg++;
	}
	printf("ended da shit with %i\n", i);
	str[i] = '\0';
	printf ("just copied %s with len %i\n", str, (int)ft_strlen(str));
	return (str);
}

char	*get_next_arg(char *args, char **pointers, int done)
{
	static int	current;
	char		*str;
	int			start;

	while (ft_isblank(args[current]))
		current++;
	start = current;
	while (args[current] && !ft_isblank(args[current]))
	{
		if (is_quote(args[current]))
			current += goto_next_quote(&args[current]) + 1;
		else
			current++;
	}
	str = copy_argument(&args[start], current - start);
	if (!str)
	{
		clear_ptr_array(pointers);
		exit_program(OUT_OF_MEMORY);
	}
	if (done)
		current = 0;
	return (str);
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
			args += goto_next_quote(args) + 1;
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
	int		i;
printf("Im receiving %s\n", args);
	pointers = NULL;
	if (!args)
		return (NULL);
	size = count_args(args);
	pointers = malloc(sizeof(char *) * (size + 1));
	if (!pointers)
		exit_program(OUT_OF_MEMORY);
	i = 0;
	while (i <= size)
		pointers[i++] = NULL;
	i = 0;
	while (i < size)
	{
		pointers[i] = get_next_arg(args, pointers, i == size - 1);
		i++;
	}
	printf ("size is %i\n", size);
	printargs(pointers);
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