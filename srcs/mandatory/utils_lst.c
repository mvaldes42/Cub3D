/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 13:50:22 by mvaldes           #+#    #+#             */
/*   Updated: 2020/04/29 18:12:10 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*ft_lstnew_map(char *line)
{
	t_map	*lst;

	if (!(lst = malloc(sizeof(t_map))))
	{
		g_error = 3;
		return (NULL);
	}
	lst->line = line;
	lst->next = NULL;
	return (lst);
}

t_map	*ft_lstlast_map(t_map *lst)
{
	t_map	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back_map(t_map **alst, t_map *new)
{
	t_map	*tmp;

	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
		(ft_lstlast_map(*alst))->next = new;
}

void	ft_lstclear_map(t_map **lst)
{
	t_map	*tmp;
	t_map	*next;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}

int		ft_lstsize_map(t_map *lst)
{
	t_map	*tmp;
	int		i;

	i = 0;
	if (!lst)
		return (i);
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
