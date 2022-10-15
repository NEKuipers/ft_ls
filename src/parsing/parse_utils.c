/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 19:29:22 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/16 00:31:41 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	print_file_not_found(char *target)
{
	write(2, "ft_ls: ", 7);
	write(2, target, ft_strlen(target));
	write(2, ": No such file or directory\n", 28);
}

int	number_of_flags(int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i] && i < ac)
	{
		if (av[i][0] == '-')
			i++;
		else
			break ;
	}
	return (i - 1);
}

int	arg_in_dir_operands(char *arg, t_data *data)
{
	int	i;

	if (data->dir_operands == NULL)
		return (0);
	i = 0;
	while (data->dir_operands[i])
	{
		if (ft_strcmp(arg, data->dir_operands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
