/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 16:38:35 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/03/03 13:28:02 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*new;

	new = (void *)malloc(count * size);
	if (!(new))
		return (NULL);
	ft_bzero(new, count * size);
	return (new);
}
