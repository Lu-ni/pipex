/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:08:20 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/25 22:30:09 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_getlen(long num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	if (num < 0)
		len++;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		signe;
	int		len;
	char	str[20];

	signe = 1;
	len = ft_getlen(n);
	if (n < 0)
		signe = -1;
	if (n == 0)
		str[0] = '0';
	str[len] = '\0';
	while (n)
	{
		str[--len] = (n % 10) * signe + '0';
		n /= 10;
	}
	if (signe == -1)
		str[0] = '-';
	ft_putstr_fd(str, fd);
}
