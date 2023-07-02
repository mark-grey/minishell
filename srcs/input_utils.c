/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:20:34 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/02 14:22:38 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* VERIFICA SE É QUOTE
 * Comportamento do bash quando não encontra fechamento do quote:
 * 	bash: unexpected EOF while looking for matching quote.
 * 	bash: syntax error: unexpected end of file
 */
int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

/* VERIFICA SE É CARACTERE DE REDIRECIONADOR
 */
int	is_redirector_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

/* VERIFICA SE É REDIRECIONADOR
 */
int	is_redirector(char *red)
{
	return (\
		!ft_strncmp(red, ">>\0", 3) || \
		!ft_strncmp(red, "<<\0", 3) || \
		!ft_strncmp(red, ">\0", 2) || \
		!ft_strncmp(red, "<\0", 2) || \
		!ft_strncmp(red, "|\0", 2));
}

/* VERIFICA SE É BUILTIN
 */
int	is_builtin(char *cmd)
{
	return (\
		!ft_strncmp(cmd, "ping\0", 5) || \
		!ft_strncmp(cmd, "cd\0", 3) || \
		!ft_strncmp(cmd, "pwd\0", 4) || \
		!ft_strncmp(cmd, "echo\0", 5) || \
		!ft_strncmp(cmd, "unset\0", 6) || \
		!ft_strncmp(cmd, "export\0", 7) || \
		!ft_strncmp(cmd, "env\0", 4) || \
		!ft_strncmp(cmd, "exit\0", 5));
}

/* VERIFICA SE É EXEC
 */
int	is_exec(char *path, char *cmd)
{
	char	*exec_path;
	char	*temp_path;
	size_t	len;

	if (!path || !cmd)
		return (0);
	len = ft_strlen(path);
	temp_path = malloc(sizeof(char) * len + 1);
	if (!temp_path)
		return (0);
	ft_strlcpy(temp_path, path, len);
	exec_path = NULL;
	exec_path = parse_path(temp_path, cmd);
	free(temp_path);
	if (exec_path)
	{
		free(exec_path);
		return (1);
	}
	return (0);
}
