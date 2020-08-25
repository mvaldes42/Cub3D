/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:02:09 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/25 14:04:59 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "cub3d.h"

void		free_p(void *p)
{
	if (p)
		free(p);
}

void		close_fd(int fd)
{
	if (fd)
		close(fd);
}

void		exit_message_failure(int count, ...)
{
	va_list	args;
	void	*ptr;
	int		error;

	va_start(args, count);
	exit_sequence(va_arg(args, t_env *));
	error = va_arg(args, int);
	if (count > 2 && (ptr = va_arg(args, void *)))
		free_p(ptr);
	ft_putstr_fd("Error\n", 1);
	write(1, error[g_errorm].msg, ft_strlen(error[g_errorm].msg));
	va_end(args);
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
