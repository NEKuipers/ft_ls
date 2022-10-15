/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 19:29:22 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/15 19:36:15 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_no_such_file(char *target)
{
	write(2, "ft_ls: ", 7);
	write(2, target, ft_strlen(target));
	write(2, ": No such file or directory\n", 28);
}

int number_of_flags(int argc, char **argv)
{
	int i;

	i = 1;
	while (argv[i] && i < argc)
	{
		if (argv[i][0] == '-')
			i++;
		else
			break;
	}
	return (i - 1);
}
