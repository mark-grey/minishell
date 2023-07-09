/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:10:09 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/09 10:37:56 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//change path to variable home
static int	change_to_home_path(t_env *env)
{
	t_env	*home;

	home = search_var("HOME", env);
	if (!home)
	{
		perror("cd: HOME not set");
		return (-1);
	}
	if (chdir(home->value))
		return (0);
	perror("cd: chdir failed");
	return (-1);
}

//change path to path
static int	change_to_arg_path(char *path)
{
	if (chdir(path))
		return (0);
	perror("cd: chdir failed");
	return (-1);
}

int	b_cd(char **path, t_env *env)
{
	if (!env)
		return (-1);
	else if ((*path)[1])
		return (perror("cd: too many arguments"), 1);
	else if (!(*path))
		return (change_to_home_path(env));
	else
		return (change_to_arg_path(*path));
}

/* ERROS POSSÍVEIS DO COMANDO "Change Directory"

	"Home directory not set": Ocorre quando o diretório inicial do usuário (home
	directory) não está configurado corretamente.

	"Too many arguments": Indica que foram fornecidos argumentos extras com o
	comando cd. O cd aceita apenas um único argumento, que é o diretório para o
	qual se deseja mudar.
	
	____________________
	"No such file or directory": Indica que o diretório especificado não existe.
	
	"Permission denied": Significa que o usuário atual não tem permissão para
	acessar o diretório desejado.
	
	"Not a directory": O caminho fornecido para o cd não aponta para um
	diretório válido, mas sim para um arquivo ou outro tipo de objeto do sistema.

	"Too many symbolic links": Refere-se a um loop de links simbólicos, onde o
	caminho contém um número excessivo de referências simbólicas que levam a uma
	recursão infinita.

	"Invalid option": Indica que uma opção inválida foi fornecida juntamente com
	o comando cd. Geralmente, o cd não aceita opções em muitos shells, mas isso
	pode variar dependendo do ambiente.

	"Not a valid directory": Significa que o caminho especificado não corresponde
	a um diretório válido no sistema de arquivos.

	"Read-only file system": Ocorre quando o sistema de arquivos em que o
	diretório está localizado está montado apenas para leitura. Nesse caso, não
	é possível navegar para outros diretórios.

	____________________
	-1 na saída do 'chdir' indica que ocorreu um erro ao tentar mudar de diretório.
	Nesse caso, você pode usar a variável errno para obter mais informações sobre o
	erro específico. Alguns possíveis valores de errno associados ao chdir incluem:

		ENOENT (No such file or directory): O diretório especificado não existe.
		EACCES (Permission denied): O usuário não tem permissão de acesso ao dir.
		ENOTDIR (Not a directory): O caminho fornecido não é um diretório válido.
		EFAULT (Bad address): O ponteiro para o caminho do diretório é inválido.
		EROFS (Read-only file system): O diretório é somente de leitura.
		ENOENT (No such file or directory): Indica que o diretório especificado
			não existe.
		ELOOP (Too many symbolic links): Número excessivo de referências simbólicas
			(recursão infinita).
		EIO (Input/output error): Indica um erro de entrada/saída genérico que pode
			ocorrer ao acessar o diretório.
*/