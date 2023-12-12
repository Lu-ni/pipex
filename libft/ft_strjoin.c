/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:48:05 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/24 17:49:08 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinstr;
	char	*startstr;
	int		i;

	if (!s1 || !s2)
		return ((char *)0);
	joinstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joinstr)
		return ((char *)0);
	startstr = joinstr;
	i = 0;
	while (s1[i])
		*joinstr++ = s1[i++];
	i = 0;
	while (s2[i])
		*joinstr++ = s2[i++];
	*joinstr = '\0';
	return (startstr);
}
