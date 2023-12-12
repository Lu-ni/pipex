/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:33:47 by lnicolli          #+#    #+#             */
/*   Updated: 2023/10/30 15:24:04 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_free(void *ptr)
{
	free(ptr);
	return (1);
}

static char	*ft_sanityze(const char *str, char c, char **strfinal)
{
	char	*strcpy;
	char	*strclean;
	char	*startofclean;
	char	*startofcpy;

	strcpy = ft_strdup(str);
	if (!strcpy)
		return ((char *)0);
	startofcpy = strcpy;
	strclean = ft_calloc(ft_strlen(str) + 1, 1);
	startofclean = strclean;
	if (!strclean && ft_free(startofcpy))
		return ((char *)0);
	while (*strcpy && *strcpy == c)
		strcpy++;
	while (*strcpy)
	{
		if (*strcpy != c || (*(strcpy + 1) && *(strcpy + 1) != c))
			*strclean++ = *strcpy;
		strcpy++;
	}
	free(startofcpy);
	*strfinal = startofclean;
	return (startofclean);
}

static void	ft_create_str(char *str, char c, int *words)
{
	int	i;

	*words = 1;
	i = 0;
	if (!*str)
	{
		*words = 0;
		return ;
	}
	while (str[i])
		if (str[i++] == c)
			*words += 1;
}

static int	ft_countchar(char *str, char c)
{
	char	*strcpy;
	int		count;

	count = 0;
	strcpy = str;
	while (*strcpy && *strcpy++ != c)
		count++;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**strlist;
	int		words;
	int		i;
	char	*startstr;

	if (!ft_sanityze(s, c, &str))
		return ((char **)0);
	startstr = str;
	ft_create_str(str, c, &words);
	strlist = malloc((words + 1) * sizeof(char *));
	if (!strlist && ft_free(startstr))
		return (strlist);
	i = 0;
	while (i < words)
	{
		strlist[i] = ft_substr(str, 0, ft_countchar(str, c));
		if (!strlist[i] && ft_free(startstr))
			return ((char **)0);
		str += ft_countchar(str, c) + 1;
		i++;
	}
	strlist[i] = (char *)0;
	free(startstr);
	return (strlist);
}
