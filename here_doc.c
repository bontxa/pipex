/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:22:03 by aboncine          #+#    #+#             */
/*   Updated: 2022/11/28 15:12:06 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	here_doc2(t_pipex box, char **argv)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(argv[2], "\n");
	str = get_next_line(0);
	while (str)
	{
		if (cmp(str, tmp) == 1)
		{
			close(1);
			free(str);
			free(tmp);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(str, box.pipefd[1]);
		free (str);
		str = get_next_line(0);
	}
	close(1);
	free(str);
	free(tmp);
	close(box.pipefd[0]);
	close(box.pipefd[1]);
}

void	here_doc(t_pipex box, char **argv)
{
	pid_t	pid;

	box.i = 3;
	pid = fork();
	if (pid == 0)
		here_doc2(box, argv);
	else
	{
		waitpid(pid, NULL, 0);
		close(box.pipefd[1]);
		dup2(box.pipefd[0], 0);
		close(box.pipefd[0]);
	}
}
