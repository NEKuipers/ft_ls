/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 12:40:45 by nkuipers      #+#    #+#                 */
/*   Updated: 2022/10/15 20:58:40 by nickkuipers   ########   odam.nl         */
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

typedef struct s_data
{
	char		*flags;
	char		**targetdirs;
	char		**targetfiles;
	t_directory	*founddirectories;
	t_file		*foundfiles;
	int			argc;
}				t_data;

/*
 * Parsing
 */
char			**find_targets(char **argv, int flag_args, t_data *data, char type);
t_data			*parse_input(int argc, char** argv);
char			*parse_ls_flags(char **argv, int amount);
int				arg_is_in_dir_targets(char *arg, t_data *data);
void			print_no_such_file(char *target);
int				number_of_flags(int argc, char **argv);

void			error_and_exit(char *reason, char *flags);

#endif
