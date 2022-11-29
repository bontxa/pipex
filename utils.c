/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:50:47 by aboncine          #+#    #+#             */
/*   Updated: 2022/11/28 15:12:27 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	checkchar(int c, char const *s)
{
	if (s[c] == 34 || s[c] == 39)
		return (1);
	return (0);
}

int	cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	error_exit(int i)
{
	if (i == 1)
	{
		write(2, "Error:\n bad file descriptor\n", 28);
		exit(127);
	}
	if (i == 2)
	{
		write(2, "Error: command not found\n", 25);
		exit (127);
	}
}

void	libera_tutto(char **args, char *tmp, char **path)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	i = 0;
	while (path[i])
		free(path[i++]);
	free(args);
	free(path);
	free(tmp);
	error_exit(2);
}
