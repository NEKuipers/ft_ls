/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 21:47:11 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/13 00:13:55 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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

char	*parse_ls_flags(char **argv)
{
	int		i;
	int		j;
	int		flagcounter;
	char	*flags;

	flagcounter = 0;
	i = 1;
	flags = ft_strdup("XXXXX");
	while (argv[i])
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

int	count_target_amount(int argc, char **argv, char type)
{
	struct	stat path_stat;
	int	amount;

	amount = 0;
	while (argc > 1) {
		argc--;
   		stat(argv[argc], &path_stat);
		if (type == 'd' && S_ISDIR(path_stat.st_mode)) {
			amount++;
		} else if (type == 'f' && S_ISREG(path_stat.st_mode)) {
			amount++;
		}
	}
	return amount;
}

//TODO fix Weird bug when ./ft_ls [folder] [flag] [file] -> flag is considered file
char	**find_targets(int argc, char **argv, char type)
{
	struct	stat path_stat;
	char	**targets;
	int		amount;
	int		i;

	amount = count_target_amount(argc, argv, type);
	if (amount == 0)
		return NULL;
	targets = (char **)malloc(amount * sizeof(char *));
	i = 0;
	while (argc > 1) {
		argc--;
   		stat(argv[argc], &path_stat);
		if (type == 'f' && S_ISREG(path_stat.st_mode)) {
			targets[i] = ft_strdup(argv[argc]);
			i++;
		} else if (type == 'd' && S_ISDIR(path_stat.st_mode)) {
			targets[i] = ft_strdup(argv[argc]);
			i++;
		}
	}
	return targets;
}
