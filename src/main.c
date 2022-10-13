/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 17:49:31 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/13 00:15:07 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	error_and_exit(char *reason, char *flags)
{
	char	*errormessage;

	errormessage = ft_strjoin("Error: ", reason);
	write(2, errormessage, ft_strlen(errormessage));
	free(errormessage);
	free(flags);
	exit(1);
}

int count_total_targets(t_ls_data ls_data)
{
	int count;
	
	count = 0;
	if (ls_data.targetdirs != 0)
		count = sizeof(ls_data.targetdirs) / 8;
	if (ls_data.targetfiles != 0)
		count += sizeof(ls_data.targetfiles) / 8;
	return count;
}

int	main(int argc, char **argv)
{
	char		*flags;
	t_ls_data	ls_data;

	ls_data.targetdirs = find_targets(argc, argv, 'd');
	ls_data.targetfiles = find_targets(argc, argv, 'f');
	
	flags = parse_ls_flags(argv, argc - count_total_targets(ls_data) - 1);
	if (flags[0] == 'E')
		error_and_exit("invalid flag\n", flags);
	if (ls_data.targetdirs != NULL) {
		for (int x = 0; ls_data.targetdirs[x]; x++) {
			ft_printf("target dir: %s\n", ls_data.targetdirs[x]);
		}
	}
	if (ls_data.targetfiles != NULL) {
		for (int x = 0; ls_data.targetdirs[x]; x++) {
			ft_printf("target file: %s\n",ls_data.targetfiles[x]);
		}
	}
	ft_printf("flags: %s\n", flags);
	// get_file_information(flags, &ls_data);
	// sort_data(flags, &ls_data);
	// print_data(flags, &ls_data);
	if (flags)
		free(flags);
	return (0);
}
