/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 15:09:01 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/18 15:59:29 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	free_array(char **array)
{
	int	i;
	
	i = 0;
	if (array)
	{
		while (array[i] != NULL)
        {
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_input(t_input *input)
{
	if (input->flags)
		free(input->flags);
//    if (input->dir_operands)
//    	free_array(input->dir_operands);
}

void	free_files(t_file **files)
{
	int	i;

	i = 0;
	if (files != NULL)
	{
		while (files[i] != NULL)
		{
			free(files[i]->filename);
			free(files[i]->filepath);
			free(files[i]->permissions);
			free(files[i]->owner_name);
			free(files[i]->owner_group);
			free(files[i]);
			i++;
		}
        free(files);
	}
}

void	free_data(t_data *data)
{
	int i;

	i = 0;
	if (data->flags)
		free(data->flags);
	if (data->files)
		free_files(data->files);
    if (data->directories)
	{
		while (data->directories[i])
		{
			free_files(data->directories[i]->files);
			free(data->directories[i]->dir_path);
			free(data->directories[i]);
			i++;
		}
		free(data->directories);
	}
}