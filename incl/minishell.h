/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:09:26 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/11 14:02:54 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/incl/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <curses.h>
# include <termios.h>
# include <termcap.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>

// Structs
typedef struct	s_env
{
	char			*key;
	char			*value;
	struct	s_env	*next;
}					t_env;

// Functions
int		is_builtin(char *str, t_env *env_list);
int		is_exec(char *path, char *command);
char	*path_parser(char *path, char *command);
t_env	*parse_env(char **env);
t_env	*ft_add_var(t_env *prev, char *var);
t_env	*ft_search_var(char *str, t_env *list);
void	ft_remove_var(char *str, t_env *list);
void	ft_set_var(const char *src, t_env *node);
void	print_var_list(t_env *list);
void	clear_var_list(t_env *list);
char	*get_var_value(char *value, t_env *env_list);

#endif