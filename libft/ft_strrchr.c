/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:48:05 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/24 17:49:09 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*lastoccurence;
	char	*strcpy;

	lastoccurence = (char *)0;
	strcpy = (char *)str;
	while (*strcpy)
	{
		if (*strcpy == (char)c)
			lastoccurence = strcpy;
		strcpy++;
	}
	if ((char)c == '\0')
		return (strcpy);
	if (lastoccurence != (char *)0)
		return (lastoccurence);
	return ((char *)0);
}
