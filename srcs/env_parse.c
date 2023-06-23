/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:34:50 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/22 21:01:54 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* SETAR VARIÁVEL
 * Coloca um novo par chave-valor em um node.
 * Caso já exista algum valor alocado na key,
 * dará free neste valor antes de setar um novo.
 */
void	set_var(const char *src, t_env *node)
{
	int		len;
	char	*dst;
	char	*c;

	if (node->key)
		free (node->key);
	len = ft_strlen(src) + 1;
	dst = malloc(sizeof(char) * len);
	if (!dst)
		exit(1);
	ft_strlcpy(dst, src, len);
	c = ft_strchr(dst, '=');
	*c = '\0';
	node->key = dst;
	node->value = ++c;
}

/* CRIAR VARIÁVEL
 * Cria um novo node e coloca no final da lista.
 */
t_env	*add_var(t_env *prev, char *var)
{
	t_env	*newnode;

	newnode = malloc(sizeof(t_env));
	if (!newnode)
		exit(1);
	*newnode = (t_env){0};
	if (prev)
		prev->next = newnode;
	set_var(var, newnode);
	return (newnode);
}

/* BUSCAR VARIÁVEL
 * Procura uma variável na lista, e, caso não
 * encontre, retorna nulo.
 */
t_env	*search_var(char *str, t_env *list)
{
	int	size;

	size = ft_strlen(str) + 1;
	while (list)
	{
		if (!ft_strncmp(str, list->key, size))
			return (list);
		list = list->next;
	}
	return (NULL);
}

/* REMOVER VARIÁVEL
 * Através do endereço do item anterior da lista,
 * é deletado o item desejado.
 */
t_env	*remove_var(char *str, t_env *list)
{
	t_env	*prev;
	t_env	*current;

	if (!str || !list)
		return (list);
	prev = NULL;
	current = list;
	while (current)
	{
		if (!ft_strncmp(str, current->key, ft_strlen(str) + 1))
		{
			if (prev == NULL)
				list = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
	return (list);
}

/* PARSE ENV
 * Distribui cada uma das variáveis de env em uma lista linkada.
 */
t_env	*parse_env(char **env)
{
	t_env	*env_list;
	t_env	*prev_env;

	env_list = add_var(NULL, *env++);
	prev_env = env_list;
	while (*env)
	{
		prev_env = add_var(prev_env, *env);
		env++;
	}
	return (env_list);
}
