/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:05:53 by mvaldes           #+#    #+#             */
/*   Updated: 2019/11/19 12:06:00 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		word_count(const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;

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

static char		**no_occurence(char **dest, const char *s)
{
	dest[0] = ft_strdup(s);
	dest[1] = 0;
	return (dest);
}

static char		**ft_split2(char const *s, char c)
{
	int		start;
	int		end;
	int		i;
	char	**dest;

	start = 0;
	end = 0;
	i = 0;
	if (!(dest = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1))))
		return (NULL);
	while (i != word_count(s, c))
	{
		while (s[start] == c)
			start++;
		if (!s[start])
			return (no_occurence(dest, s));
		end = start;
		while (s[end] != c && s[end])
			end++;
		dest[i] = ft_substr(s, start, (end - start));
		i++;
		start = end;
	}
	dest[i] = 0;
	return (dest);
}

char			**ft_split(char const *s, char c)
{
	if (!(s))
		return (NULL);
	return (ft_split2(s, c));
}
