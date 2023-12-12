/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:48:05 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/30 13:07:27 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*startsubstr;

	if (!s)
		return ((char *)0);
	if (start >= ft_strlen(s))
	{
		substr = (char *)malloc(1);
		if (!substr)
			return ((char *)0);
		substr[0] = '\0';
		return (substr);
	}
	if (ft_strlen(&s[start]) >= len)
		substr = (char *)malloc(len + 1);
	else
		substr = (char *)malloc(ft_strlen(&s[start]) + 1);
	if (!substr)
		return ((char *)0);
	startsubstr = substr;
	while (s[start] && (len-- > 0))
		*substr++ = s[start++];
	*substr = '\0';
	return (startsubstr);
}
