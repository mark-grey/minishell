/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:42:01 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/10 14:54:36 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* SETAR VARIÁVEL
 * Coloca um novo par chave-valor em um node.
 * Caso já exista algum valor alocado na key,
 * dará free neste valor antes de setar um novo.
 */
void	ft_set_var(const char *src, t_env *node)
{
	int		len;
	char	*dst;
	char	*c;

	if (node->key)
		free (node->key);
	len	= ft_strlen(src) + 1;
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
t_env	*ft_add_var(t_env *prev, char *var)
{
	t_env *newnode;

	newnode = malloc(sizeof(t_env));
	if (!newnode)
		exit(1);
	if (prev)
		prev->next = newnode;
	printf("teste\n");
	newnode->next = NULL;
	ft_set_var(var, newnode);
	return (newnode);
}

/* BUSCAR VARIÁVEL
 * Procura uma variável na lista, e, caso não
 * encontre, retorna nulo.
 */
t_env	*ft_search_var(char *str, t_env *list)
{
	int	size;

	size = ft_strlen(str);
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
void	ft_remove_var(char *str, t_env *list)
{
	t_env	*temp;
	int		size;

	size = ft_strlen(str) + 1;
	while (list)
	{
		if (!ft_strncmp(str, list->next->key, size))
			break ;
		list = list->next;
	}
	free(list->next->key);
	temp = list->next;
	list->next = list->next->next;
	free(temp);
}
