/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:04:03 by aboncine          #+#    #+#             */
/*   Updated: 2022/11/23 18:27:53 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
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
			splitted[b] = crea(s, i);
			b++;
			splitted[b] = 0;
			return (splitted);
		}
		else if (s[i] != c && check == 0)
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
} */














static void libera_tutto(char **args, char *tmp, char **path)
{
	int i;

	i = 0;
	while (args[i])
		free(args[i++]);
	i = 0;
	while (path[i])
		free(path[i++]);
	free(args);
	free(path);
	free(tmp);
	perror("command not found");
	exit (127);
}

static void	do_first2(char **path,  int *i, char **args)
{
	char	*tmp2;

	*i = 0;
	while (path[*i])
	{
		tmp2 = ft_strjoin(path[*i], "/");
		free (path[*i]);
		path[*i] = ft_strjoin (tmp2, args[0]);
		free (tmp2);
		if(access(path[*i], F_OK) == 0)
			break;
		(*i)++;
	}
}

static void	do_first(char *argv, char **envp)
{
	int		i;
	char	*tmp;
	char	**args;
	char	**path;

	i = 0;
	args = ft_split2(argv, ' ');
	if(access(argv, F_OK) == 0)
		execve(argv, args, envp);
	while (envp[i][0] != 'P' || envp[i][1] != 'A'
	|| envp[i][2] != 'T' || envp[i][3] != 'H')
		i++;
	tmp = ft_strtrim(envp[i], "PATH=");
	path = ft_split(tmp, ':');
	do_first2(path, &i, args);
	if (path[i] == 0)
		libera_tutto(args, tmp, path);
	if(execve(path[i], args, envp) == -1)
		libera_tutto(args, tmp, path);
}

static void	babbo(char *argv, char **envp, int *pipefd, int fdoutput)
{
	dup2(pipefd[0], 0);
	dup2(fdoutput, 1);
	close(pipefd[1]);
	close(pipefd[0]);
	do_first(argv, envp);
}

static void	figlio(char *argv, char **envp, int *pipefd, int fdinput)
{
	dup2(fdinput, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	do_first(argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	int		fdinput;
	int		fdoutput;

	if (argc == 5)
	{
		fdinput = open(argv[1], O_RDONLY);
		if(fdinput < 0)
			perror("Error");
		fdoutput = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if(fdoutput < 0)
			exit(127);
		if (pipe(pipefd) < 0)
			perror("Pipe Error:");
		pid = fork();
		if (pid == 0)
			figlio(argv[2], envp, pipefd, fdinput);
		if (pid > 0)
			babbo(argv[3], envp, pipefd, fdoutput);
	}
	else
	{
		perror("Error: command not found");
		exit (EXIT_FAILURE);
	}
}
