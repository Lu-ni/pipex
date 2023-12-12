/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:48:05 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/24 17:49:07 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	void	*string1;
	void	*string2;

	string1 = (void *)s1;
	string2 = (void *)s2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*(unsigned char *)string1 != *(unsigned char *)string2)
			return (*(unsigned char *)string1 - *(unsigned char *)string2);
		string1++;
		string2++;
		n--;
	}
	return (0);
}
