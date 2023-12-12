/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:48:05 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/24 17:49:08 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*srccpy;

	if (dstsize == 0)
		return (ft_strlen(src));
	srccpy = (char *)src;
	dstsize--;
	while (*srccpy && (dstsize > 0))
	{
		*dst++ = *srccpy++;
		dstsize--;
	}
	if (dstsize >= 0)
		*dst = '\0';
	return (ft_strlen(src));
}
