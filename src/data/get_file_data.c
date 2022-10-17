/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_file_data->c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nickkuipers <nickkuipers@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 13:35:02 by nickkuipers   #+#    #+#                 */
/*   Updated: 2022/10/17 17:19:40 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>

static char	*get_file_permissions(int fd)
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

t_file	*get_file_data(char *filename)
{
	t_file			*file;
	struct stat		buf;

	file = (t_file *)malloc(sizeof(t_file)); //here
	ft_memset(file, '\0', sizeof(t_file));
	file->filename = ft_strdup(filename);
	if (stat(filename, &buf) == 0)
	{
		//TODO consider symbolic links (lstat()?)
		file->permissions = get_file_permissions(buf.st_mode);
		file->number_of_links = buf.st_nlink;
		file->owner_group = ft_strdup(getgrgid(buf.st_gid)->gr_name);
		file->owner_name = ft_strdup(getpwuid(buf.st_uid)->pw_name);
		file->file_size = buf.st_size;
		file->last_modified_time = buf.st_mtime;
	}
	else
		return NULL; //TODO error handling
	return (file);
}
