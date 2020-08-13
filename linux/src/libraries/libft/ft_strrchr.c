/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:48:32 by mvaldes           #+#    #+#             */
/*   Updated: 2020/01/09 13:14:39 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *str;

	if (s != NULL)
	{
		str = NULL;
		while (*s)
		{
			if (*s == (char)c)
				str = (char *)s;
			s++;
		}
		if (*s == (char)c)
			str = (char *)s;
		return (str);
	}
	return (NULL);
}
