/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:53:08 by mvaldes           #+#    #+#             */
/*   Updated: 2020/01/09 13:07:17 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst_cpy;
	char	*src_cpy;

	if (dst != NULL && src != NULL && dst != src)
	{
		dst_cpy = (char *)dst;
		src_cpy = (char *)src;
		if (src_cpy <= dst_cpy)
		{
			while (len--)
				((unsigned char*)dst_cpy)[len] = ((unsigned char*)src_cpy)[len];
		}
		else
		{
			i = 0;
			while (i < len)
			{
				((unsigned char*)dst_cpy)[i] = ((unsigned char*)src_cpy)[i];
				i++;
			}
		}
		return (dst_cpy);
	}
	return (NULL);
}
