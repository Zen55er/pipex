/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:35:12 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/28 11:56:01 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	plug_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
	return ;
}

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
	return ;
}
