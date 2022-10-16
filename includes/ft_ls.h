/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 12:40:45 by nkuipers      #+#    #+#                 */
/*   Updated: 2022/10/16 23:23:10 by nickkuipers   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/time.h>
# include "../lib/libft/libft.h"

typedef struct s_file
{
	char			*filename;
	char			*permissions;
	int				number_of_links;
	char			*owner_name;
	char			*owner_group;
	int				file_size;
	long			last_modified_time;
	int				blocks;
}					t_file;

typedef struct s_directory
{
	char		*dir_path;
	int			blocks;
	t_file		*file;
}				t_directory;

typedef struct s_data
{
	char		*flags; //TODO move flags to data struct
	t_directory	**found_dirs;
	t_file		**found_files;
}				t_data;

typedef struct s_input
{
	int			ac;
	char		**dir_operands;
	char		**file_operands;
	char		*flags;
}				t_input;

/*
 * Parsing
 */
t_input			*parse_input(int ac, char **av);
char			*parse_ls_flags(char **av, int amount);
char			**find_operands(char **av, int flag_args, \
					t_input *input, char type);
int				arg_in_dir_operands(char *arg, t_input *input);
void			print_file_not_found(char *target);
int				number_of_flags(int ac, char **av);

/*
 * File data
 */
t_data			get_data(t_input *input);
t_file			*get_file_info(char *filename);
char			*get_file_permissions(int fd);

/*
 * Utils
 */
void			free_input(t_input *input);
void			free_data(t_data data);
void			error_and_exit(char *reason, t_data data);

#endif
