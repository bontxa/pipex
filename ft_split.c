/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:28:17 by aboncine          #+#    #+#             */
/*   Updated: 2022/10/07 12:23:07 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	countwords(char const *s, char c)
{
	int	count;
	int	i;
	int	check;

	count = 0;
	i = 0;
	check = 0;
	while (s[i])
	{
		if (s[i] != c && check == 0)
		{
			count++;
			check = 1;
		}
		else if (s[i] == c)
			check = 0;
		i++;
	}
	return (count);
}

static char	*c_words(char const *s, char c, int start)
{
	char	*new;
	int		i;
	int		begin;

	i = 0;
	begin = start;
	while (s[start] != c && s[start] != '\0')
	{
		i++;
		start++;
	}
	new = malloc (sizeof(char) * i + 1);
	i = 0;
	if (!new)
		return (NULL);
	while (s[begin] != c && s[begin] != '\0')
	{
		new[i] = s[begin];
		i++;
		begin++;
	}
	new[i] = '\0';
	return (new);
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	int		i;
	int		b;
	int		check;

	splitted = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1));
	i = 0;
	b = 0;
	check = 0;
	while (s[i])
	{
		if (s[i] != c && check == 0)
		{
			splitted[b] = c_words(s, c, i);
			b++;
			check = 1;
		}
		if (s[i] == c)
			check = 0;
		i++;
	}
	splitted[b] = NULL;
	return (splitted);
}
