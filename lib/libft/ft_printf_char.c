/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_char.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:37:29 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/03/12 13:54:05 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd_count(char c, int fd, int *rv)
{
	write(fd, &c, 1);
	*rv += 1;
}

static char	ternary(int zero)
{
	if (zero == 1)
		return ('0');
	else
		return (' ');
}

void	printchar(t_flags *flags, va_list list, int *rv)
{
	if (flags->width == 0 || flags->width == 1)
		ft_putchar_fd_count(va_arg(list, int), 1, rv);
	else if (flags->width > 1 && flags->leftj == 0)
	{
		while (flags->width > 1)
		{
			ft_putchar_fd_count(ternary(flags->zero), 1, rv);
			flags->width--;
		}
		ft_putchar_fd_count(va_arg(list, int), 1, rv);
	}
	else if (flags->width > 1 && flags->leftj == 1)
	{
		ft_putchar_fd_count(va_arg(list, int), 1, rv);
		while (flags->width > 1)
		{
			ft_putchar_fd_count(ternary(flags->zero), 1, rv);
			flags->width--;
		}
	}
}

void	print_percent(t_flags *flags, int *rv)
{
	if (flags->width == 0 || flags->width == 1)
		ft_putchar_fd_count('%', 1, rv);
	else if (flags->width > 1 && flags->leftj == 0)
	{
		while (flags->width > 1)
		{
			ft_putchar_fd_count(ternary(flags->zero), 1, rv);
			flags->width--;
		}
		ft_putchar_fd_count('%', 1, rv);
	}
	else if (flags->width > 1 && flags->leftj == 1)
	{
		ft_putchar_fd_count('%', 1, rv);
		while (flags->width > 1)
		{
			ft_putchar_fd_count(ternary(flags->zero), 1, rv);
			flags->width--;
		}
	}
}
