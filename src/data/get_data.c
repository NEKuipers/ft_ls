/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 00:25:46 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/18 23:00:23 by nickkuipers   ########   odam.nl         */
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
	i = 0;
	while (file_operands[i])
	{
		files[i] = get_file_data(file_operands[i]);
		if (files[i] == NULL)
		{
			return (NULL);
		}
		i++;
	}
	files[i] = NULL;
	free_array(file_operands);
	return (files);
}

char	**subdir_recursive(char *directory)
{
	DIR				*dir;
	struct dirent	*dirp;
	char			**new;
	
	new = NULL;
	dir = opendir(directory);
	while ((dirp = readdir(dir)) != NULL)
	{
		if (dirp->d_type == DT_DIR && ft_strcmp(directory, ".") != 0 && ft_strcmp(directory, "..") != 0)
		{
			return (string_array_join(new, subdir_recursive(dirp->d_name)));
		}
	}
	closedir(dir);
	return (new);
}

char	**find_subdirectories(char **dir_operands)
{
	int		i;
	char	**new;
	
	i = 0;
	new = NULL;
	while (dir_operands[i] != NULL)
		new = string_array_join(new, subdir_recursive(dir_operands[i++]));
	return (new);
}

t_directory **get_dirs_from_operands(char **dir_operands, char *flags)
{
	t_directory	**directories;
	int			i;

	i = 0;
	if (ft_strchr(flags, 'R'))
		dir_operands = find_subdirectories(dir_operands);
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

t_data	get_data(t_input *input)
{
	t_data	data;

	data.flags = ft_strdup(input->flags);
    data.directories = NULL;
    data.files = NULL;
	if (input->dir_operands == NULL && input->file_operands == NULL)
	{
		input->dir_operands = (char **)malloc(sizeof(char *) * 2);
		input->dir_operands[0] = ft_strdup(".");
		input->dir_operands[1] = NULL;
	}
	data.first_dir_operand_flag = arr_size(input->dir_operands);
	if (input->file_operands != NULL)
	{
		data.first_dir_operand_flag = 0;
		data.files = get_files_from_operands(input->file_operands);
		if (data.files == NULL)
		{
			free_input(input);
			error_and_exit(" something went wrong opening file.", data);
		}
	}
	if (input->dir_operands != NULL)
		data.directories = get_dirs_from_operands(input->dir_operands, data.flags);
	return (data);
}
