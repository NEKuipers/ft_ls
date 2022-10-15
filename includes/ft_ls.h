/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 12:40:45 by nkuipers      #+#    #+#                 */
/*   Updated: 2022/10/15 18:19:39 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../lib/libft/libft.h"

typedef struct s_file
{
	char		*permissions;
	int			number_of_links;
	char		*owner_name;
	char		*owner_group;
	int			file_size;
	int			day_last_modified;
	char		*month_last_modified;
	int			hours_last_modified;
	int			minutes_last_modified;
	char		*filename;
}				t_file;

typedef struct s_directory
{
	char		*dirname;
	int			blocks;
	t_file		*file;
}				t_directory;

typedef struct s_ls_data
{
	char		*flags;
	char		**targetdirs;
	char		**targetfiles;
	t_directory	*founddirectories;
	t_file		*foundfiles;
}				t_ls_data;

char			**find_targets(int argc, char **argv, int flag_args, char type);
char			*parse_ls_flags(char **argv, int amount);

#endif
