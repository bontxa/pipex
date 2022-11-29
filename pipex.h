/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:56:20 by aboncine          #+#    #+#             */
/*   Updated: 2022/11/28 15:12:18 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <sys/wait.h>
# include "get_next_line.h"

typedef struct s_pipex
{
	int	i;
	int	pipefd[2];
	int	fin;
	int	fout;
}	t_pipex;

char	**ft_split2(char const *s, char c);
void	libera_tutto(char **args, char *tmp, char **path);
void	error_exit(int i);
int		checkchar(int c, char const *s);
int		cmp(char *s1, char *s2);
void	here_doc(t_pipex box, char **argv);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putstr_fd(char *s, int fd);

#endif
