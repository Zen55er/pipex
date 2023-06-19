/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:35:12 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/19 11:50:20 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Creates pipes*/
int	create_pipes(t_fds *fds, int ac)
{
	int	i;

	fds->pipes = ac - 4 - fds->here_doc;
	fds->pipefd = (int **)malloc(sizeof(int *) * (fds->pipes + 1));
	if (!fds->pipefd)
		return (1);
	i = -1;
	while (++i < fds->pipes)
	{
		fds->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fds->pipefd[i])
			return (big_free(0, 0, fds->pipefd, 0));
		if (pipe(fds->pipefd[i]) == -1)
		{
			perror("Piping failed");
			return (big_free(0, 0, fds->pipefd, 0));
		}
	}
	fds->pipefd[i] = 0;
	fds->fake = 0;
	fds->i_pipe = 0;
	fds->i = -1;
	return (0);
}

/*Closes used pipes*/
void	plug_pipes(t_fds *fds)
{
	int	i;

	i = -1;
	while (++i < fds->pipes)
	{
		close(fds->pipefd[i][0]);
		close(fds->pipefd[i][1]);
	}
	return ;
}

/*Selects appropriate case to send to new_process*/
void	get_flag(int i, int ac, t_fds *fds)
{
	if (i == 0)
		(*fds).flag = 0;
	else if (i + 2 + fds->here_doc == ac - 2)
		(*fds).flag = 2;
	else
		(*fds).flag = 1;
	return ;
}

/*Updates input and output fd's according to case*/
void	get_in_out(t_fds *fds)
{
	if ((*fds).flag == 0)
	{
		(*fds).in = (*fds).in_fd;
		(*fds).out = (*fds).pipefd[0][1];
	}
	else if ((*fds).flag == 1)
	{
		(*fds).in = (*fds).pipefd[fds->i_pipe - 1][0];
		(*fds).out = (*fds).pipefd[fds->i_pipe][1];
	}
	else if ((*fds).flag == 2)
	{
		(*fds).in = (*fds).pipefd[fds->i_pipe - 1][0];
		(*fds).out = (*fds).out_fd;
	}
}

void	prep_pids(t_fds *fds)
{
	int	total_pids;

	total_pids = fds->pipes + 1;
	fds->pids = (pid_t *)malloc(sizeof(pid_t) * total_pids);
	return ;
}
