/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 12:40:45 by nkuipers      #+#    #+#                 */
/*   Updated: 2022/10/16 00:52:50 by nickkuipers   ########   odam.nl         */
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
	char		**dir_operands;
	char		**file_operands;
	t_directory	*founddirectories;
	t_file		*foundfiles;
	int			ac;
}				t_data;

/*
 * Parsing
 */
t_data			*parse_input(int ac, char **av);
char			*parse_ls_flags(char **av, int amount);
char			**find_operands(char **av, int flag_args, \
					t_data *data, char type);
int				arg_in_dir_operands(char *arg, t_data *data);
void			print_file_not_found(char *target);
int				number_of_flags(int ac, char **av);

/*
 * File data
 */
void			get_filedata(t_data *data);


/*
 * Utils
 */
void			free_data(t_data *data);
void			error_and_exit(char *reason, char *flags);

#endif
