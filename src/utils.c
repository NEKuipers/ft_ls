/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:08:53 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/16 00:52:34 by nickkuipers   ########   odam.nl         */
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

//TODO write funcions that free the directory and file objects

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->flags)
		free(data->flags);
	if (data->dir_operands)
	{
		while (data->dir_operands[i] != NULL)
			free(data->dir_operands[i++]);
		free(data->dir_operands);
	}
	i = 0;
	if (data->file_operands)
	{
		while (data->file_operands[i] != NULL)
			free(data->file_operands[i++]);
		free(data->file_operands);
	}
	free(data);
}
