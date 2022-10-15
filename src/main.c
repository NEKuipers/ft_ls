/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 17:49:31 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/16 00:35:19 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = parse_input(ac, av);

	// //Debugging block 
	// ft_printf("flags: %s\n", data->flags);
	// if (data->dir_operands) {
	// 	for (int x = 0; data->dir_operands[x]; x++) {
	// 		ft_printf("target dir: %s\n", data->dir_operands[x]);
	// 	}
	// }
	// if (data->file_operands) {
	// 	for (int x = 0; data->file_operands[x]; x++) {
	// 		ft_printf("target file: %s\n",data->file_operands[x]);
	// 	}
	// }

	
	get_filedata(data);
	// sort_data(data);
	// print_data(data);
	free_data(data);
	return (0);
}
