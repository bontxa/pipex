/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:40:19 by aboncine          #+#    #+#             */
/*   Updated: 2022/11/28 15:12:22 by aboncine         ###   ########.fr       */
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
		if (s[i] == 34 || s[i] == 39)
		{
			count++;
			return (count);
		}
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

static char	*crea(char const *s, int start)
{
	int		i;
	char	*new;
	char	c;

	i = 1;
	c = s[start];
	while (s[start + i] != c)
		i++;
	new = malloc (sizeof(char) * i);
	i = 0;
	start++;
	while (s[start] != c)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
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

static void	do_all(char const *s, int i, char c, char **splitted)
{
	int		b;
	int		check;

	b = 0;
	check = 0;
	while (s[i])
	{
		if (checkchar(i, s) == 1 && check == 0)
		{
			splitted[b++] = crea(s, i);
			splitted[b] = 0;
			return ;
		}
		else if (s[i] != c && check == 0)
		{
			splitted[b++] = c_words(s, c, i);
			check = 1;
		}
		if (s[i] == c)
			check = 0;
		i++;
	}
	splitted[b] = NULL;
}

char	**ft_split2(char const *s, char c)
{
	char	**splitted;
	int		i;

	splitted = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!splitted)
		return (NULL);
	i = 0;
	do_all(s, i, c, splitted);
	return (splitted);
}
