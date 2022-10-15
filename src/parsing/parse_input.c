/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 21:47:11 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/16 00:37:03 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

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

char	*parse_ls_flags(char **av, int amount)
{
	int		i;
	int		j;
	int		flagcounter;
	char	*flags;

	flagcounter = 0;
	i = 1;
	flags = ft_strdup("XXXXX");
	while (av[i] && i < amount + 1)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][0] == '-' && j > 0 && ft_strchr("Ralrt", av[i][j]))
			{
				if (!is_dupl(flags, av[i][j]))
					flags[flagcounter++] = av[i][j];
			}
			j++;
		}
		i++;
	}
	return (flags);
}

static int	count_operand_amount(char **av, int flag_args, t_data *data, \
		char type)
{
	struct stat	path_stat;
	int			amount;
	int			i;

	amount = 0;
	i = 0;
	while ((flag_args + i + 1) < data->ac)
	{
		i++;
		if (stat(av[flag_args + i], &path_stat) == 0)
		{
			if ((type == 'd' && S_ISDIR(path_stat.st_mode)) || \
				(type == 'f' && S_ISREG(path_stat.st_mode)))
				amount += 1;
		}
		else
		{
			if (type == 'f' && !arg_in_dir_operands(av[flag_args + i], data))
				print_file_not_found(av[flag_args + i]);
		}
	}
	return (amount);
}

//Something in printf is fucked when using multiple variables...
char	**find_operands(char **av, int flag_args, t_data *data, char type)
{
	struct stat	path_stat;
	char		**targets;
	int			amount;
	int			i;

	amount = 0;
	amount = count_operand_amount(av, flag_args, data, type);
	if (amount == 0)
		return (NULL);
	targets = (char **)malloc((amount + 1) * sizeof(char *));
	i = 0;
	while ((flag_args + 1) < data->ac)
	{
		if (stat(av[flag_args + 1], &path_stat) == 0)
		{
			if ((type == 'd' && S_ISDIR(path_stat.st_mode)) || \
				(type == 'f' && S_ISREG(path_stat.st_mode)))
				targets[i++] = ft_strdup(av[flag_args + 1]);
		}
		flag_args++;
	}
	targets[i] = NULL;
	return (targets);
}

t_data	*parse_input(int ac, char **av)
{
	int		number_of_flag_arguments;
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->ac = ac;
	number_of_flag_arguments = number_of_flags(ac, av);
	data->flags = parse_ls_flags(av, number_of_flag_arguments);
	data->dir_operands = find_operands(av, number_of_flag_arguments, data, 'd');
	data->file_operands = find_operands(av, number_of_flag_arguments, data, 'f');
	if (data->flags[0] == 'E')
		error_and_exit("invalid flag\n", data->flags);
	return (data);
}