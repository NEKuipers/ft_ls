/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 21:47:11 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/15 19:07:27 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#define FOUND_DIR (type == 'd' && S_ISDIR(path_stat.st_mode))
#define FOUND_FILE (type == 'f' && S_ISREG(path_stat.st_mode))

/*
* Flags XXXXX : R a l r t
* The five required flags are above
* If one is found in parsing, it is set
* If anything else is found, first flag is set to E for error
*/

int	flag_is_duplicate(char *flags, char f)
{
	int	i;

	i = 0;
	while (flags[i] != '\0')
	{
		if (flags[i] == f)
			return (1);
		i++;
	}
	return (0);
}

char	*parse_ls_flags(char **argv, int amount)
{
	int		i;
	int		j;
	int		flagcounter;
	char	*flags;

	flagcounter = 0;
	i = 1;
	flags = ft_strdup("XXXXX");
	while (argv[i] && i < amount + 1)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][0] == '-' && (j > 0 && !ft_strchr("Ralrt", (argv[i][j]))))
			{
				flags[0] = 'E';
				return (flags);
			}
			if (argv[i][0] == '-' &&  j > 0 && !flag_is_duplicate(flags, argv[i][j])) {
				flags[flagcounter++] = argv[i][j];
			}
			j++;
		}
		i++;
	}
	return (flags);
}

int	count_target_amount(int argc, char **argv, int flag_args, char type)
{
	struct	stat path_stat;
	int	amount;
	int	i;

	amount = 0;
	i = 0;
	while ((flag_args + i + 1) < argc)
	{
		i++;
   		stat(argv[flag_args + i], &path_stat);
		if (FOUND_DIR || FOUND_FILE)
			amount += 1;
	}

	return (amount);
}

//Something in printf is fucked
char	**find_targets(int argc, char **argv, int flag_args, char type)
{
	struct stat	path_stat;
	char	**targets;
	int	amount;
	int	i;

	amount = 0;
	amount = count_target_amount(argc, argv, flag_args, type);

	if (amount == 0)
		return (NULL);
	targets = (char **)malloc((amount + 1) * sizeof(char *));
	ft_printf("amount is %i\n", amount);
	i = 0;
	while ((flag_args + i + 1) < argc)
	{
		stat(argv[flag_args + i + 1], &path_stat);
		if (FOUND_DIR || FOUND_FILE) {
			targets[i] = ft_strdup(argv[flag_args + i + 1]);
			if (type == 'f') {
				ft_printf("%s\n", argv[i]);
			}
		}
		i++;
	}
	targets[i] = NULL;
	return (targets);
}
