/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_files.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 00:25:46 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/16 20:54:18 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"
/*
 *	figure out which data to get based on operands and flags:
 *		- get a list of targets from operands
 *	 	- get data from the targets based on flags: 
 *	    	- a includes hidden files/dirs (start with .)
 *	     	- l is long format
 * 			- R is recursive, going all the way down...
 * 		files always go before directories
 */


t_file	*get_file_info(char *filename)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	ft_memset(file, '\0', sizeof(t_file));
	file->filename = ft_strdup(filename);
	return file;
}

t_data	get_data(t_input *input)
{
	int		i;
	t_data	data;

	i = 0;
	data.flags = NULL;
	data.found_dirs = NULL;
	data.found_files = NULL;

	if (input->dir_operands == NULL && input->file_operands == NULL)
	{
		input->dir_operands = (char **)malloc(sizeof(char *) * 2);
		input->dir_operands[0] = ft_strdup(".");
		input->dir_operands[1] = NULL;
	}
	if (input->file_operands != NULL)
	{
		while (input->file_operands[i])
			i++;
		data.found_files = (t_file **)malloc(sizeof(t_file *) * (i + 1));
		data.found_files[i] = NULL;
		i = 0;
		while (input->file_operands[i])
		{
			data.found_files[i] = get_file_info(input->file_operands[i]);
			i++;
		}
	}
	// if (data->dir_operands != NULL)
	// 	get_dir_information(data);
	return (data);
}
