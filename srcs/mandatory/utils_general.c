/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:02:09 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/05 15:30:40 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		exit_message_failure(void)
{
	printf("Error\n%s\n", g_error[g_errorm].msg);
	exit(EXIT_FAILURE);
}

void		print_map(t_map *map)
{
	t_map	*current_line;

	current_line = map;
	while (current_line != NULL)
	{
		printf("%s\n", current_line->line);
		current_line = current_line->next;
	}
}
