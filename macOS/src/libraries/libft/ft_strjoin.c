/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:57:18 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/22 11:56:17 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	while (src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (*dest);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		length;
	char	*result;

	if (!(s1) || !(s2))
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	if (!(result = malloc((sizeof(char)) * (length + 1))))
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	return (result);
}
