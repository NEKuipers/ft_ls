/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 21:47:11 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/15 21:03:13 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#define FOUND_DIR (type == 'd' && S_ISDIR(path_stat.st_mode))
#define FOUND_FILE (type == 'f' && S_ISREG(path_stat.st_mode))


#include <errno.h>
#include <string.h>
/*
* Flags XXXXX : R a l r t
* The five required flags are above
* If one is found in parsing, it is set
* If anything else is found, first flag is set to E for error
*/

static int	is_dupl(char *flags, char f)
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
			if (argv[i][0] == '-' && j > 0 && !is_dupl(flags, argv[i][j]))
				flags[flagcounter++] = argv[i][j];
			j++;
		}
		i++;
	}
	return (flags);
}

static int	count_target_amount(char **argv, int flag_args, t_data *data, char type)
{
	struct	stat path_stat;
	int	amount;
	int	i;

	amount = 0;
	i = 0;
	while ((flag_args + i + 1) < data->argc)
	{
		i++;
   		if (stat(argv[flag_args + i], &path_stat) == 0) {
			if (FOUND_DIR || FOUND_FILE)
				amount += 1;
		} else {
			if (type == 'f' && !arg_is_in_dir_targets(argv[flag_args + i], data)) 
				print_no_such_file(argv[flag_args + i]);
		}
	}

	return (amount);
}

//Something in printf is fucked
char	**find_targets(char **argv, int flag_args, t_data *data, char type)
{
	struct stat	path_stat;
	char	**targets;
	int	amount;
	int	i;

	amount = 0;
	amount = count_target_amount(argv, flag_args, data, type);

	if (amount == 0)
		return (NULL);
	targets = (char **)malloc((amount + 1) * sizeof(char *));
	i = 0;
	while ((flag_args + 1) < data->argc)
	{
		if (stat(argv[flag_args + 1], &path_stat) == 0){
			if (FOUND_DIR || FOUND_FILE)
				targets[i++] = ft_strdup(argv[flag_args + 1]);
		}
		flag_args++;
	}
	targets[i] = NULL;
	return (targets);
}

t_data	*parse_input(int argc, char** argv)
{
	int	number_of_flag_arguments;
	t_data	*data;
	
	data = (t_data *)malloc(sizeof(t_data));
	data->argc = argc;
	number_of_flag_arguments = number_of_flags(argc, argv);
	data->flags = parse_ls_flags(argv, number_of_flag_arguments);
	data->targetdirs = find_targets(argv, number_of_flag_arguments, data, 'd');
	data->targetfiles = find_targets(argv, number_of_flag_arguments, data, 'f');
	if (data->flags[0] == 'E')
		error_and_exit("invalid flag\n", data->flags);	
	return (data);
}
