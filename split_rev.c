/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_rev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:58:53 by aboncine          #+#    #+#             */
/*   Updated: 2022/11/23 18:27:56 by aboncine         ###   ########.fr       */
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
			return(count);
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

char *crea(char const *s, int start)
{
	int i;
	char *new;
	char c;

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
	return(new);
}

int checkchar(int c, char const *s)
{
	if(s[c] == 34 || s[c] == 39)
		return(1);
	return (0);
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

char	**ft_split2(char const *s, char c)
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
		if (checkchar(i, s) == 1 && check == 0)
		{
			splitted[b++] = crea(s, i);
			splitted[b] = 0;
			return (splitted);
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
	return (splitted);
}
