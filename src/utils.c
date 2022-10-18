/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:08:53 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/17 19:51:45 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	error_and_exit(char *reason, t_data data)
{
	char	*errormessage;

	errormessage = ft_strjoin("Error: ", reason);
	write(2, errormessage, ft_strlen(errormessage));
	free(errormessage);
	free_data(&data);
	exit(1);
}

void	free_array(char **array)
{
	int	i;
	
	i = 0;
	if (array)
	{
		while (array[i] != NULL) {
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
	free_array(input->dir_operands);
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

void	el()
{
	write(2, "Check\n", 6);
}

char	*join_path(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = '/';
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
