/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:38:27 by aboncine          #+#    #+#             */
/*   Updated: 2022/10/07 12:23:51 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_stop(char const *s1, char const *set)
{
	size_t	i;
	size_t	x;
	size_t	last;

	i = ft_strlen(s1) - 1;
	x = 0;
	last = ft_strlen(s1);
	while (set[x])
	{
		if (s1[i] == set[x])
		{
			if (last == 0)
				return (last);
			last--;
			x = 0;
			i--;
		}
		else
			x++;
	}
	return (last);
}

static size_t	ft_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	x;
	size_t	first;

	i = 0;
	x = 0;
	first = 0;
	while (set[x])
	{
		if (s1[i] == set[x])
		{
			first++;
			x = 0;
			i++;
		}
		else
			x++;
	}
	return (first);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	size_t	i;
	size_t	first;
	size_t	last;

	i = 0;
	first = ft_start(s1, set);
	last = ft_stop(s1, set);
	if (s1[first] == '\0')
	{
		first = 0;
		last = 0;
	}
	p = (char *) malloc(sizeof(char) * (last - first + 1));
	if (!p)
		return (NULL);
	while (first < last)
	{
		p[i] = s1[first];
		i++;
		first++;
	}
	p[i] = '\0';
	return (p);
}
