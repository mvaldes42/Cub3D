/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:38:08 by mvaldes           #+#    #+#             */
/*   Updated: 2020/01/09 15:22:04 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if (count != 0 && size != 0)
	{
		if (!(result = malloc(size * count)))
			return (NULL);
		ft_bzero(result, size * count);
		return (result);
	}
	return (malloc(1));
}
