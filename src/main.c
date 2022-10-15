/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 17:49:31 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/15 19:06:05 by nickkuipers   ########   odam.nl         */
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

void	free_ls_data(t_ls_data *ls_data)
{
	int	i;
	
	i = 0;
	if (ls_data->flags)
		free(ls_data->flags);

	if (ls_data->targetdirs) {
		while (ls_data->targetdirs[i] != NULL) 
			free(ls_data->targetdirs[i++]);
		free(ls_data->targetdirs);
	}

	i = 0;
	if (ls_data->targetfiles) {
		while (ls_data->targetfiles[i] != NULL) 
			free(ls_data->targetfiles[i++]);
		free(ls_data->targetfiles);
	}
	free(ls_data);
}

//if flags are specified after the target file/dir, print 'No such file or directory'.

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

t_ls_data	*parse_input(int argc, char** argv)
{
	int	number_of_flag_arguments;
	t_ls_data	*ls_data;
	
	ls_data = (t_ls_data *)malloc(sizeof(t_ls_data));
	number_of_flag_arguments = number_of_flags(argc, argv);
	ls_data->flags = parse_ls_flags(argv, number_of_flag_arguments);
	ls_data->targetdirs = find_targets(argc, argv, number_of_flag_arguments, 'd');
	ls_data->targetfiles = find_targets(argc, argv, number_of_flag_arguments, 'f');
	if (ls_data->flags[0] == 'E')
		error_and_exit("invalid flag\n", ls_data->flags);	
	return (ls_data);
}

int	main(int argc, char **argv)
{
	t_ls_data	*ls_data;

	ls_data = parse_input(argc, argv);
	
	//Debugging block 
	ft_printf("flags: %s\n", ls_data->flags);
	if (ls_data->targetdirs) {
		for (int x = 0; ls_data->targetdirs[x]; x++) {
			ft_printf("target dir: %s\n", ls_data->targetdirs[x]);
		}
	}
	if (ls_data->targetfiles) {
		for (int x = 0; ls_data->targetfiles[x]; x++) {
			ft_printf("target file: %s\n",ls_data->targetfiles[x]);
		}
	}
	// get_file_information(flags, &ls_data);
	// sort_data(flags, &ls_data);
	// print_data(flags, &ls_data);
	free_ls_data(ls_data);
	return (0);
}
