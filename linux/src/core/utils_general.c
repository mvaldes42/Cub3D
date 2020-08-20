/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:02:09 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/12 20:24:17 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "cub3d.h"

void		exit_message_failure(int error)
{
	(void)error;
	ft_putstr_fd("Error\n", 1);
	write(1, error[g_errorm].msg, ft_strlen(error[g_errorm].msg));
	exit(EXIT_FAILURE);
}

int			ft_isnum(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] <= 47 || str[i] >= 58) && (str[i] != 32))
			return (0);
		i++;
	}
	return (1);
}

int			word_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}
