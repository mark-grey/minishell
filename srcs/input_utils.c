/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:20:34 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/26 20:39:31 by maalexan         ###   ########.fr       */
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
int	is_redirector(char c)
{
	return (c == '>' || c == '<' || c == '|');
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

	if (!cmd)
		return (0);
	exec_path = NULL;
	if (path)
	{
		len = ft_strlen(path);
		temp_path = malloc(sizeof(char) * len + 1);
		if (!temp_path)
			exit_program(OUT_OF_MEMORY);
		ft_strlcpy(temp_path, path, len);
		exec_path = parse_path(temp_path, cmd);
		free(temp_path);
	}
	else
		exec_path = parse_path(NULL, cmd);
	if (exec_path)
		return (free(exec_path), 1);
	return (0);
}
