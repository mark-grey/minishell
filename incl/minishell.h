/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:09:26 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/10 20:47:31 by maalexan         ###   ########.fr       */
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

# define OUT_OF_MEMORY 1

// Structs
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cli
{
	char			*cmd;
	char			**args;
	char			*director;
	char			*exec;
	struct s_cli	*next;
}					t_cli;

typedef struct s_ctrl
{
	t_cli	*cli;
	t_env	*env;
	char	*exec_path;
}			t_ctrl;

/* STRINGIFY FUNCTIONS */
char	**stringify_envp(t_env *list);
char	**stringify_args(char *args);
int		count_list(t_env *list);

/* PARSE ENV FUNCTIONS */
// Main
t_env	*parse_env(char **env);
void	update_env(char **argv, char *cmd);

// Utils
t_env	*add_var(t_env *prev, char *var);
t_env	*search_var(char *str, t_env *list);
t_env	*remove_var(char *str, t_env *list);
char	*get_var_value(char *value, t_env *env_list);
void	set_var(const char *src, t_env *node);
void	clear_command_input(t_cli *cli);
void	clear_ptr_array(char **array);
void	exit_program(int code);

/* PARSE INPUT FUNCTIONS */
// Main
t_cli	*parse_input(char *input, char *path);
char	*expand_line(char *line);

// Validators
int		is_builtin(char *cmd);
int		is_exec(char *path, char *cmd);
int		is_redirector(char *red);
int		is_bracket(char c);
int		is_pipe(char c);
int		is_quote(char c);
int		bar_input(char *input);
char	*parse_path(char *path, char *cmd);

// Gets
t_ctrl	*get_control(void);
char	*get_cli(char *input, int *i);
char	*get_redirector(char *input, int *i);
char	*get_cmd(char *cli, int *start, int *end, char *path);
char	*get_args(char *cli, int *start, int *end);
int		get_quote(char *input, int *i);

/* BUILTINS */
// Main
void	call_builtin(char *builtin, char **args, t_env *env);

// Commands
int		b_cd(char **path, t_env *env);
void	b_echo(char **args);
void	b_env(t_env *list);
void	b_export(t_env *env, char **args);
void	b_pwd(void);
void	b_unset(t_env *env, char **args);

#endif