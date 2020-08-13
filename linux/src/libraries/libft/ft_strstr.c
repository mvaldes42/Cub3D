/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 11:12:06 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/11 11:16:40 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hay, const char *needle)
{
	size_t n;
	size_t len;

	if (hay != NULL && needle != NULL && *needle)
	{
		n = ft_strlen(needle);
		len = ft_strlen(hay);
		while (*hay && len-- >= n)
		{
			if (ft_strncmp(hay, needle, n) == 0)
				return ((char *)hay);
			hay++;
		}
		return (NULL);
	}
	return ((char *)hay);
}
