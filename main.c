/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:04:03 by aboncine          #+#    #+#             */
/*   Updated: 2022/11/15 15:45:04 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void libera_tutto(t_pipex *box)
{
	box->len = 0;
	while (box->args[box->len])
		free(box->args[box->len++]);
	box->len = 0;
	while (box->path[box->len])
		free(box->path[box->len++]);
	free(box->args);
	free(box->path);
	free(box->tmp);
}

static void	do_first(t_pipex *box, char *argv, char **envp)
{
	box->len = 0;
	while (envp[box->len][0] != 'P' || envp[box->len][1] != 'A' || envp[box->len][2] != 'T'
		|| envp[box->len][3] != 'H')
		box->len++;

	box->tmp = ft_strtrim(envp[box->len], "PATH=");
	box->path = ft_split(box->tmp, ':');
	box->args = ft_split(argv, ' ');
	box->len = 0;
	while (box->path[box->len])
	{
		box->path[box->len] = ft_strjoin(box->path[box->len], "/");
		box->path[box->len] = ft_strjoin(box->path[box->len], box->args[0]);
		box->len++;
	}
	box->len = 0;
	while (access(box->path[box->len], F_OK) != 0 && box->path[box->len])
		box->len++;
	if (box->path[box->len] == 0)
		perror("Errore");
	execve(box->path[box->len], box->args, envp);
}

static void	babbo(t_pipex *box, char *argv, char **envp)
{
	dup2(box->pipefd[0], 0);
	dup2(box->fdoutput, 1);
	close(box->pipefd[1]);
	close(box->pipefd[0]);
	do_first(box, argv, envp);
}

static void	figlio(t_pipex *box, char *argv, char **envp)
{
	dup2(box->fdinput, 0);
	dup2(box->pipefd[1], 1);
	close(box->pipefd[0]);
	close(box->pipefd[1]);
	do_first(box, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*box;
	pid_t	pid;
	box = (t_pipex *) malloc(sizeof(t_pipex));
	if (!box)
		return (0);
	if (argc > 1)
	{
		box->fdinput = open("map.ber", O_RDONLY);
		box->fdoutput = open("test", O_WRONLY);
		if(box->fdoutput < 0)
			perror("errore");
		if (pipe(box->pipefd) < 0)
			perror("Pipe Error:");
		pid = fork();
		if (pid == 0)
			figlio(box, argv[2], envp);
		if (pid > 0)
			babbo(box, argv[3], envp);
		libera_tutto(box);
		free(box);
	}
	else
	{
		perror("Errore");
		free (box);
	}
}
