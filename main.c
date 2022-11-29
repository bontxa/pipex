/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:57:24 by aboncine          #+#    #+#             */
/*   Updated: 2022/11/28 15:12:10 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	do_first2(char **path, int *i, char *args)
{
	char	*tmp2;

	*i = 0;
	while (path[*i])
	{
		tmp2 = ft_strjoin(path[*i], "/");
		free (path[*i]);
		path[*i] = ft_strjoin (tmp2, args);
		free (tmp2);
		if (access(path[*i], F_OK) == 0)
			break ;
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
	if (access(argv, F_OK) == 0)
		execve(argv, args, envp);
	while (envp[i][0] != 'P' || envp[i][1] != 'A'
	|| envp[i][2] != 'T' || envp[i][3] != 'H')
		i++;
	tmp = ft_strtrim(envp[i], "PATH=");
	path = ft_split(tmp, ':');
	do_first2(path, &i, args[0]);
	if (path[i] == 0)
		libera_tutto(args, tmp, path);
	if (execve(path[i], args, envp) == -1)
		libera_tutto(args, tmp, path);
}

static void	figlio(t_pipex box, int argc, char **argv, char **envp)
{
	pid_t	pid;

	while (box.i < argc - 2)
	{
		pipe(box.pipefd);
		pid = fork();
		if (pid == 0)
		{
			close(box.pipefd[0]);
			dup2(box.pipefd[1], 1);
			close(box.pipefd[1]);
			do_first(argv[box.i], envp);
		}
		else
		{
			close(box.pipefd[1]);
			dup2(box.pipefd[0], 0);
			close(box.pipefd[0]);
		}
		box.i++;
	}
}

static void	main2(int argc, char **argv, char **envp)
{
	t_pipex	box;

	if (argc >= 6 && cmp(argv[1], "here_doc") == 1)
	{
		pipe(box.pipefd);
		here_doc(box, argv);
		box.fout = open(argv[argc - 1], O_APPEND | O_CREAT | O_RDWR, 0000644);
		if (box.fout < 0)
			error_exit(1);
	}
	else
	{
		box.i = 2;
		box.fin = open(argv[1], O_RDONLY);
		if (box.fin < 0)
			write(2, "Error:\n bad file descriptor\n", 28);
		dup2(box.fin, 0);
		box.fout = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (box.fout < 0)
			error_exit(1);
	}
	figlio(box, argc, argv, envp);
	dup2(box.fout, 1);
	do_first(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
		main2(argc, argv, envp);
	else
		error_exit(2);
}
