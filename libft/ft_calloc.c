/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:48:05 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/24 20:24:18 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	int		totalbyte;

	mem = (char *)malloc(count * size);
	if (!mem)
		return ((void *)0);
	totalbyte = size * count;
	while (totalbyte > 0)
	{
		mem[totalbyte - 1] = (char)0;
		totalbyte--;
	}
	return ((void *)mem);
}
