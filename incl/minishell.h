/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:09:26 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/22 20:43:18 by maalexan         ###   ########.fr       */
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
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}					t_args;

typedef struct s_cli
{
	char			*command;
	char			*args;
	char			*director;
	struct s_cli	*next;
}					t_cli;

// Functions
int		is_builtin(char *str, t_env *env_list);
int		is_exec(char *path, char *command);
char	*path_parser(char *path, char *command);
char	*find_exec(char *path, char *command);
t_env	*parse_env(char **env);
t_env	*ft_add_var(t_env *prev, char *var);
t_env	*ft_search_var(char *str, t_env *list);
t_env	*ft_remove_var(char *str, t_env *list);
void	ft_set_var(const char *src, t_env *node);
void	print_var_list(t_env *list);
void	clear_var_list(t_env *list);
int		count_list(t_env *list);
char	*get_var_value(char *value, t_env *env_list);
char	**stringify_envp(t_env *list);

// PARSE
// Validator Functions
int		is_bt(char *cmd);
int		is_ex(char *cmd);
int		is_redirector(char c);
int		is_quote(char c);

// Get Functions
void	get_quote(char *input, int *i);
char	*get_cli(char *input, int *i);
char	*get_redirector(char *input, int *i);
char	*get_command(char *cli, int *start, int *end);
char	*get_args(char *cli, int *start, int *end);

#endif