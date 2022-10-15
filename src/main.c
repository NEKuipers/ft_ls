/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 17:49:31 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/15 21:03:33 by nickkuipers   ########   odam.nl         */
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

void	free_data(t_data *data)
{
	int	i;
	
	i = 0;
	if (data->flags)
		free(data->flags);

	if (data->targetdirs) {
		while (data->targetdirs[i] != NULL) 
			free(data->targetdirs[i++]);
		free(data->targetdirs);
	}

	i = 0;
	if (data->targetfiles) {
		while (data->targetfiles[i] != NULL) 
			free(data->targetfiles[i++]);
		free(data->targetfiles);
	}
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = parse_input(argc, argv);
	
	//Debugging block 
	ft_printf("flags: %s\n", data->flags);
	if (data->targetdirs) {
		for (int x = 0; data->targetdirs[x]; x++) {
			ft_printf("target dir: %s\n", data->targetdirs[x]);
		}
	}
	if (data->targetfiles) {
		for (int x = 0; data->targetfiles[x]; x++) {
			ft_printf("target file: %s\n",data->targetfiles[x]);
		}
	}
	// get_file_information(flags, &data);
	// sort_data(flags, &data);
	// print_data(flags, &data);
	free_data(data);
	while(1);
	return (0);
}
