/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 21:47:11 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/17 18:16:00 by nickkuipers   ########   odam.nl         */
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

static int	count_operand_amount(char **av, int flag_args, t_input *input, \
		char type)
{
	struct stat	buf;
	int			amount;
	int			i;

	amount = 0;
	i = 0;
	while ((flag_args + i + 1) < input->ac)
	{
		i++;
		if (stat(av[flag_args + i], &buf) == 0)
		{
			if ((type == 'd' && S_ISDIR(buf.st_mode)) || \
				(type == 'f' && S_ISREG(buf.st_mode)))
				amount += 1;
		}
		else
		{
			if (type == 'f' && !arg_in_dir_operands(av[flag_args + i], input))
				print_file_not_found(av[flag_args + i]);
		}
	}
	return (amount);
}

//Something in printf is fucked when using multiple variables...
char	**find_operands(char **av, int flag_args, t_input *input, char type)
{
	struct stat	buf;
	char		**operands;
	int			amount;
	int			i;

	amount = 0;
	amount = count_operand_amount(av, flag_args, input, type);
	if (amount == 0)
		return (NULL);
	operands = (char **)malloc((amount + 1) * sizeof(char *));
	i = 0;
	while ((flag_args + 1) < input->ac)
	{
		if (stat(av[flag_args + 1], &buf) == 0)
		{
			if ((type == 'd' && S_ISDIR(buf.st_mode)) || \
				(type == 'f' && S_ISREG(buf.st_mode)))
				operands[i++] = ft_strdup(av[flag_args + 1]);
		}
		flag_args++;
	}
	operands[i] = NULL;
	return (operands);
}

t_input	*parse_input(int ac, char **av)
{
	int		no_of_flag_args;
	t_input	*input;

	input = (t_input *)malloc(sizeof(t_input));
	input->ac = ac;
	no_of_flag_args = number_of_flags(ac, av);
	input->flags = parse_ls_flags(av, no_of_flag_args);
	input->dir_operands = find_operands(av, no_of_flag_args, input, 'd');
	input->file_operands = find_operands(av, no_of_flag_args, input, 'f');
	return (input);
}
