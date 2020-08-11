/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:02:09 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/11 13:46:08 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "cub3d.h"

void		exit_message_failure(int error)
{
	ft_putstr_fd("Error\n", 1);
	write(1, error[g_errorm].msg, ft_strlen(error[g_errorm].msg));
	exit(EXIT_FAILURE);
}

void		print_map(t_map *map)
{
	t_map	*current_line;

	current_line = map;
	while (current_line != NULL)
	{
		write(1, current_line->line, ft_strlen(current_line->line));
		write(1, "\n", 1);
		current_line = current_line->next;
	}
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
