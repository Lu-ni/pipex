/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:48:05 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/24 21:14:51 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i_hay;
	size_t	i_needle;

	i_hay = 0;
	i_needle = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i_hay] && (len > (i_hay + i_needle)))
	{
		i_needle = 0;
		while (haystack[i_hay + i_needle] == needle[i_needle] && (len > (i_hay
					+ i_needle)))
		{
			i_needle++;
			if (!needle[i_needle] && (len > (i_hay + i_needle - 1)))
				return ((char *)(haystack + i_hay));
		}
		i_hay++;
	}
	return ((char *)0);
}
