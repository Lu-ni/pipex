/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:48:05 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/24 21:51:50 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_isinset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	int		i;

	if (!*s1)
		return (ft_strdup(""));
	i = 0;
	while (s1[i] && ft_isinset(s1[i], set))
		i++;
	start = (char *)&s1[i];
	i = ft_strlen(s1) - 1;
	while (s1[i] && ft_isinset(s1[i], set))
		i--;
	return (ft_substr(s1, start - s1, i + 1 - (start - s1)));
}
