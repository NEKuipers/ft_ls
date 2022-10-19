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

char	*join_with_separator(char *s1, char *s2, char sep)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (s1 == NULL)
        return s2;
    if (s2 == NULL)
		return (s1);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = sep;
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

char	*join_with_separator_f1(char *s1, char *s2, char sep)
{
    int		i;
    int		j;
    char	*new;

    i = 0;
    j = 0;
    if (s1 == NULL)
        return s2;
    if (s2 == NULL)
        return (s1);
    new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
    if (new == NULL)
        return (NULL);
    while (s1[i] != '\0')
    {
        new[i] = s1[i];
        i++;
    }
    new[i++] = sep;
    while (s2[j] != '\0')
        new[i++] = s2[j++];
    new[i] = '\0';
    free(s1);
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
