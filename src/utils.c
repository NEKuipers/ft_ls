/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:08:53 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/16 23:32:49 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	error_and_exit(char *reason, t_data data)
{
	char	*errormessage;

	errormessage = ft_strjoin("Error: ", reason);
	write(2, errormessage, ft_strlen(errormessage));
	free(errormessage);
	free_data(data);
	exit(1);
}

void	free_input(t_input *input)
{
	int	i;

	i = 0;
	if (input->flags)
		free(input->flags);
	if (input->dir_operands)
	{
		while (input->dir_operands[i] != NULL)
			free(input->dir_operands[i++]);
		free(input->dir_operands);
	}
	i = 0;
	if (input->file_operands)
	{
		while (input->file_operands[i] != NULL)
			free(input->file_operands[i++]);
		free(input->file_operands);
	}
}

void	free_data(t_data data)
{
	int	i;
	
	if (data.flags)
		free(data.flags);
	i = 0;
	if (data.found_files != NULL)
	{
		while (data.found_files[i] != NULL)
		{
			free(data.found_files[i]->filename);
			free(data.found_files[i]->permissions);
			free(data.found_files[i]->owner_name);
			free(data.found_files[i]->owner_group);
			free(data.found_files[i]);
			i++;
		}
	}
}
