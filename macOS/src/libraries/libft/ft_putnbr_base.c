/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:39:10 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/22 15:56:48 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putnbr_base(unsigned long nbr, char *base)
{
	long long	nb;
	long long	size;
	char		*dest;

	if (!(dest = (char *)malloc(sizeof(char) * (ft_strlen(ft_itoa(nbr)) + 1))))
		return (NULL);
	nb = nbr;
	size = ft_strlen(base);
	if (nb < 0)
		nb = nb * (-1);
	if (nb >= size)
		ft_putnbr_base(nb / size, base);
	return (strncat(dest, &(base[nb % size]), 1));
}
