/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:48:05 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/24 19:57:45 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int	initialsizedst;

	initialsizedst = ft_strlen(dst);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (ft_strlen(dst) >= dstsize)
		return (dstsize + ft_strlen(src));
	if (ft_strlen(src) < dstsize - ft_strlen(dst))
		ft_memcpy(dst + ft_strlen(dst), src, ft_strlen(src) + 1);
	else
	{
		ft_memcpy(dst + ft_strlen(dst), src, dstsize - ft_strlen(dst) - 1);
		dst[dstsize - 1] = '\0';
	}
	return (ft_strlen(src) + initialsizedst);
}
