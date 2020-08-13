/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:22:12 by mvaldes           #+#    #+#             */
/*   Updated: 2020/04/15 12:07:41 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t n;

	if (hay != NULL && needle != NULL && *needle)
	{
		n = ft_strlen(needle);
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
