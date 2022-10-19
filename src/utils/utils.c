/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:08:53 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/18 17:15:09 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	error_and_exit(char *reason, t_data data)
{
	char	*errormessage;

	errormessage = ft_strjoin("Error: ", reason);
	write(2, errormessage, ft_strlen(errormessage));
	free(errormessage);
	free_data(&data);
	exit(1);
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
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = '/';
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

int	arr_size(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

char	**string_array_join(char **s1, char **s2)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	new = (char **)malloc(sizeof(char *) * (arr_size(s1) + arr_size(s2) + 1));
	if (new == NULL)
		return (NULL);
	while (s1[i] != NULL)
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != NULL)
		new[i++] = s2[j++];
	new[i] = NULL;
//	free_array(s1);
	return (new);
}

char	**str_to_str_array(char *s1)
{
	char	**new;

	new = (char**)malloc(sizeof(char *) * 2);
	new[1] = NULL;
	new[0] = ft_strdup(s1);
	free(s1);
	return (new);
}

char	**add_string_to_array_front(char *s1, char **s2)
{
	char	**new;
	int		i;

	i = 1;
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (str_to_str_array(s1));
	new = (char **)malloc(sizeof(char *) * (2 + arr_size(s2)));
	if (new == NULL)
		return (NULL);
	new[0] = ft_strdup(s1);
	if (s1)
		free(s1);
	while (s2[i - 1] != NULL)
	{
		new[i] = s2[i - 1];
		i++;
	}
	new[i] = NULL;
	return (new);
}
