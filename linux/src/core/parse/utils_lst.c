/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 13:50:22 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/19 18:55:09 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_map	*ft_lstnew_map(void *content)
{
	t_map	*list;

	if (!(list = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	list->line = content;
	list->next = NULL;
	return (list);
}

t_map	*ft_lstlast_map(t_map *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_map(t_map **alst, t_map *new)
{
	if (alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
			ft_lstlast_map(*alst)->next = new;
	}
}

void	ft_lstdelone_map(t_map *lst, void (*del)(void *))
{
	if (del && lst)
	{
		(*del)(lst->line);
		free(lst);
	}
}

void	ft_lstclear_map(t_map **lst, void (*del)(void *))
{
	t_map	*tmp;

	if (*lst)
	{
		while ((*lst)->next)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			ft_lstdelone_map(tmp, del);
		}
		ft_lstdelone_map(*lst, del);
		*lst = NULL;
	}
}

int		ft_lstsize_map(t_map *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
