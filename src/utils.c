/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:08:53 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/15 21:11:31 by nickkuipers   ########   odam.nl         */
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
	if (data->targetdirs)
	{
		while (data->targetdirs[i] != NULL)
			free(data->targetdirs[i++]);
		free(data->targetdirs);
	}
	i = 0;
	if (data->targetfiles)
	{
		while (data->targetfiles[i] != NULL)
			free(data->targetfiles[i++]);
		free(data->targetfiles);
	}
	free(data);
}
