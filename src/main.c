/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 17:49:31 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/15 21:18:35 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = parse_input(ac, av);

	// //Debugging block 
	// ft_printf("flags: %s\n", data->flags);
	// if (data->targetdirs) {
	// 	for (int x = 0; data->targetdirs[x]; x++) {
	// 		ft_printf("target dir: %s\n", data->targetdirs[x]);
	// 	}
	// }
	// if (data->targetfiles) {
	// 	for (int x = 0; data->targetfiles[x]; x++) {
	// 		ft_printf("target file: %s\n",data->targetfiles[x]);
	// 	}
	// }

	
	// get_file_information(flags, &data);
	// sort_data(flags, &data);
	// print_data(flags, &data);
	free_data(data);
	return (0);
}
