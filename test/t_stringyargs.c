#include "minishell.h"

static void	print_args(char **args)
{
	int	i;

	i = 1;
	while (*args) {
		printf("len is %li ", ft_strlen(*args));
		printf("%i: %s\n\n", i++, *args++);
	}
}

int	main(int argc, char **argv)
{
	char	**ptrs;

	if (argc < 2)
		return (-1);
	ptrs = stringify_args(argv[1]);
	print_args(ptrs);
	clear_ptr_array(ptrs);
}

/*
gcc -Wall -Werror -Wextra -I ./incl ./test/t_stringyargs.c ./srcs/input_stringify.c ./srcs/builtin_env.c ./srcs/builtin_export.c ./srcs/builtin_caller.c ./srcs/cleaner.c ./srcs/env_parser.c ./srcs/env_utils.c ./srcs/exec_finder.c ./srcs/input_parser_gets.c ./srcs/input_parser.c ./srcs/input_utils.c  ./libs/libft/libft.a -o strin
*/