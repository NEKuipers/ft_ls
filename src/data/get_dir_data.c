/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_dir_data->c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 14:11:00 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/17 17:16:31 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

char	**find_files_in_directory(char *dirname)
{
	DIR				*directory;
	struct dirent	*dirp;
	int				i;
	char			**filenames;

	i = 0;
	directory = opendir(dirname);
	while (readdir(directory) != NULL)
		i++;
	closedir(directory);
	if (i == 0)
		return NULL;
	filenames = (char **)malloc(sizeof(char *) * (i + 1));
	directory = opendir(dirname);
	i = 0;
	while ((dirp = readdir(directory)) != NULL)
	{
		filenames[i] = join_path(dirname, dirp->d_name);
		i++;
	}
	filenames[i] = NULL;
	closedir(directory);
	return (filenames);
}

t_directory	*get_directory_data(char *dirname)
{
	t_directory	*directory;
	struct stat	buf;
	char		**contents;

	directory = (t_directory *)malloc(sizeof(t_directory));
	ft_memset(directory, '\0', sizeof(t_directory));
	directory->dir_path = ft_strdup(dirname);
	if (stat(directory->dir_path, &buf) == 0)
		directory->blocks = buf.st_blocks;
	else
		return (NULL);
	contents = find_files_in_directory(dirname);
	if (contents != NULL)
		directory->files = get_files_from_operands(contents);
	return (directory);
}
