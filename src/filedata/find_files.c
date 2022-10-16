/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_files.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 00:25:46 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/16 23:31:27 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
/*
 *	figure out which data to get based on operands and flags:
 *		- get a list of targets from operands
 *	 	- get data from the targets based on flags: 
 *	    	- a includes hidden files/dirs (start with .)
 *	     	- l is long format
 * 			- R is recursive, going all the way down...
 * 		files always go before directories
 */

char	*get_file_permissions(int fd)
{
	char	*permissions;

	permissions = (char *)malloc(11);
	ft_memset(permissions, '-', 10);
	permissions[10] = '\0';
	if (S_ISDIR(fd))
		permissions[0] = 'd';
	if (fd & S_IRUSR)
		permissions[1] = 'r';
	if (fd & S_IWUSR)
		permissions[2] = 'w';
	if (fd & S_IXUSR)
		permissions[3] = 'x';
	if (fd & S_IRGRP)
		permissions[4] = 'r';
	if (fd & S_IWGRP)
		permissions[5] = 'w';
	if (fd & S_IXGRP)
		permissions[6] = 'x';
	if (fd & S_IROTH)
		permissions[7] = 'r';
	if (fd & S_IWOTH)
		permissions[8] = 'w';
	if (fd & S_IXOTH)
		permissions[9] = 'x';
	return (permissions);
}

t_file	*get_file_info(char *filename)
{
	t_file			*file;
	struct stat		buf;

	file = (t_file *)malloc(sizeof(t_file));
	ft_memset(file, '\0', sizeof(t_file));
	file->filename = ft_strdup(filename);
	if (stat(file->filename, &buf) == 0)
	{
		file->permissions = get_file_permissions(buf.st_mode);
		file->number_of_links = buf.st_nlink;
		file->owner_group = ft_strdup(getgrgid(buf.st_gid)->gr_name);
		file->owner_name = ft_strdup(getpwuid(buf.st_uid)->pw_name);
		file->file_size = buf.st_size;
		file->last_modified_time = buf.st_mtime;
		file->blocks = buf.st_blocks;
		//TODO getgrid/pwuid return NULL if unset for some reason. handle error
	}
	// else
	// {
	// 	; //TODO handle error
	// }
	return (file);
}

t_data	get_data(t_input *input)
{
	int		i;
	t_data	data;

	i = 0;
	data.flags = ft_strdup(input->flags);
	if (input->dir_operands == NULL && input->file_operands == NULL)
	{
		input->dir_operands = (char **)malloc(sizeof(char *) * 2);
		input->dir_operands[0] = ft_strdup(".");
		input->dir_operands[1] = NULL;
	}
	if (input->file_operands != NULL)
	{
		while (input->file_operands[i])
			i++;
		data.found_files = (t_file **)malloc(sizeof(t_file) * (i + 1));
		data.found_files[i] = NULL;
		i = 0;
		while (input->file_operands[i])
		{
			data.found_files[i] = get_file_info(input->file_operands[i]);
			i++;
		}
	}
	// if (data->dir_operands != NULL)
	// 	get_dir_information(data);
	return (data);
}
