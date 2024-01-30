/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:05:44 by lnicolli          #+#    #+#             */
/*   Updated: 2023/12/13 09:42:56 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	error(char *msg, char *subject)
{
	char	str[1000];
	char	*actual;
	int		i;

	i = 0;
	actual = str;
	str[0] = '\0';
	while (*msg)
		*actual++ = *msg++;
	while (subject && *subject)
		*actual++ = *subject++;
	*actual++ = '\n';
	*actual = '\0';
	while (str[i])
		write(1, &str[i++], 1);
}
