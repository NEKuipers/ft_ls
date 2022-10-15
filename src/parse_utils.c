/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 19:29:22 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/15 21:18:02 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_no_such_file(char *target)
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

int	arg_in_dirtargets(char *arg, t_data *data)
{
	int	i;

	if (data->targetdirs == NULL)
		return (0);
	i = 0;
	while (data->targetdirs[i])
	{
		if (ft_strcmp(arg, data->targetdirs[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
