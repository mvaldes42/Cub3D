/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:02:09 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/10 18:17:46 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "cub3d.h"

void		exit_message_failure(void)
{
	ft_putstr_fd("Error\n", 1);
	write(1, g_error[g_errorm].msg, ft_strlen(g_error[g_errorm].msg));
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
