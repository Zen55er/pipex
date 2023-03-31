/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:35:12 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/31 09:58:42 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Creates both pipes*/
int	create_pipes(t_fds *fds)
{
	if (pipe((*fds).pipefd1) == -1)
		return (ft_printf("Pipe 1 failed.\n"));
	if (pipe((*fds).pipefd2) == -1)
		return (ft_printf("Pipe 2 failed.\n"));
	return (0);
}

/*Closes used pipes*/
void	plug_pipes(int pipefd1[2], int pipefd2[2])
{
	close(pipefd1[0]);
	close(pipefd1[1]);
	close(pipefd2[0]);
	close(pipefd2[1]);
	return ;
}

/*Selects appropriate case to send to new_process*/
void	get_flag(int i, int ac, t_fds *fds)
{
	if (i == 0)
		(*fds).flag = 0;
	else if (i + 2 == ac - 2 && i % 2 == 0)
		(*fds).flag = 3;
	else if (i + 2 == ac - 2 && i % 2 != 0)
		(*fds).flag = 4;
	else if (i % 2 == 0)
		(*fds).flag = 1;
	else
		(*fds).flag = 2;
	return ;
}

/*Updates input and output fd's according to case*/
void	get_in_out(t_fds *fds)
{
	if ((*fds).flag == 0)
	{
		(*fds).in = (*fds).in_fd;
		(*fds).out = (*fds).pipefd1[1];
	}
	else if ((*fds).flag == 1)
	{
		(*fds).in = (*fds).pipefd2[0];
		(*fds).out = (*fds).pipefd1[1];
	}
	else if ((*fds).flag == 2)
	{
		(*fds).in = (*fds).pipefd1[0];
		(*fds).out = (*fds).pipefd2[1];
	}
	else if ((*fds).flag == 3)
	{
		(*fds).in = (*fds).pipefd2[0];
		(*fds).out = (*fds).out_fd;
	}
	else if ((*fds).flag == 4)
	{
		(*fds).in = (*fds).pipefd1[0];
		(*fds).out = (*fds).out_fd;
	}
}
