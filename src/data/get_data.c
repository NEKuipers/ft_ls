/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_data->c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 00:25:46 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/17 18:07:06 by nickkuipers   ########   odam.nl         */
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

t_file	**get_files_from_operands(char **file_operands)
{
	t_file	**files;
	int		i;

	i = 0;
	while (file_operands[i])
		i++;
	files = (t_file **)malloc(sizeof(t_file) * (i + 1));
	files[i] = NULL;
	i = 0;
	while (file_operands[i])
	{
		files[i] = get_file_data(file_operands[i]);
		if (files[i] == NULL)
			return (NULL);
		i++;
	}
	free_array(file_operands);
	return (files);
}

t_directory **get_dirs_from_operands(char **dir_operands, char *flags)
{
	t_directory	**directories;
	int			i;

	i = 0;
	(void)flags;
	// if (ft_strchr(flags, "R"))
	// 	dir_operands = find_directories_recursively(dir_operands);
	while (dir_operands[i])
		i++;
	directories = (t_directory **)malloc(sizeof(t_directory) * (i + 1));
	directories[i] = NULL;
	i = 0;
	while (dir_operands[i])
	{
		directories[i] = get_directory_data(dir_operands[i]);
		if (directories[i] == NULL)
			return (NULL);
		i++;
	}
	return (directories);
}

t_data	*get_data(t_input *input)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->flags = ft_strdup(input->flags);
	if (input->dir_operands == NULL && input->file_operands == NULL)
	{
		input->dir_operands = (char **)malloc(sizeof(char *) * 2);
		input->dir_operands[0] = ft_strdup(".");
		input->dir_operands[1] = NULL;
	}
	if (input->file_operands != NULL)
	{
		data->files = get_files_from_operands(input->file_operands);
		if (data->files == NULL)
		{
			free_input(input);
			error_and_exit(" something went wrong opening file.", data);
			//TODO restructure error handling of file/dir parsing
		}
	}
	if (input->dir_operands != NULL)
		data->directories = get_dirs_from_operands(input->dir_operands, data->flags);
	return (data);
}
