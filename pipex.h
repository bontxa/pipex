/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:59:37 by aboncine          #+#    #+#             */
/*   Updated: 2022/11/15 15:27:35 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include "ft_printf/ft_printf.h"
typedef struct s_pipex {
char	**path;
char	*tmp;
char	**args;
int		len;
int		pipefd[2];
int		fdinput;
int		fdoutput;
}	t_pipex;

#endif
