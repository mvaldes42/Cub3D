/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:16:16 by mvaldes           #+#    #+#             */
/*   Updated: 2019/11/12 12:52:44 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	i;

	if (!s || !f)
		return (NULL);
	if (!(result = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	ft_bzero((void *)result, ft_strlen(s) + 1);
	ft_memcpy((void *)result, (const void *)s, ft_strlen(s) + 1);
	i = -1;
	while (*(result + ++i))
		*(result + i) = f(i, *(result + i));
	return (result);
}
