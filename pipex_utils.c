/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:00:15 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/28 10:01:18 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Frees everything*/
int	big_free(char **paths, t_cmds **cmds)
{
	int	i;

	if (paths)
	{
		i = -1;
		while (paths[++i])
			free (paths[i]);
		free (paths);
	}
	if (cmds)
	{
		i = -1;
		while ((*cmds)->cmd_args[++i])
			free ((*cmds)->cmd_args[i]);
		free ((*cmds)->cmd_args);
		free ((*cmds)->cmd);
		free((*cmds));
	}
	return (0);
}

/*Tests if infile can be accessed and read from*/
int	infile_test(char *path)
{
	if (access(path, F_OK))
		return (ft_printf("Infile can't be accessed.\n"));
	if (access(path, R_OK))
		return (ft_printf("Infile can't be read.\n"));
	return (0);
}

/*Tests if outfile can be accessed and has read/write permissions*/
int	outfile_test(char *path)
{
	if (access(path, F_OK))
		return (ft_printf("Outfile couldn't be accessed. File was created\n"));
	if (access(path, R_OK))
		return (ft_printf("Outfile can't be read.\n"));
	if (access(path, W_OK))
		return (ft_printf("Outfile can't be written.\n"));
	return (0);
}

int	create_pipes(t_fds *fds)
{
	if (pipe((*fds).pipefd1) == -1)
		return (ft_printf("Pipe 1 failed.\n"));
	if (pipe((*fds).pipefd2) == -1)
		return (ft_printf("Pipe 2 failed.\n"));
	return (0);
}

void	new_process_s(char *cmd, char **paths, char **envp, t_fds fds)
{
	int		new_fork;
	t_cmds	*cmds;

	fds.in = fds.in_fd;
	fds.out = fds.pipefd1[1];
	cmds = get_cmd(paths, cmd);
	new_fork = fork();
	if (new_fork < 0)
		perror("Error when forking process");
	else if (new_fork == 0)
		child(cmds, envp, fds);
}

void	new_process(char *cmd, char **paths, char **envp, t_fds fds)
{
	int		new_fork;
	t_cmds	*cmds;

	cmds = get_cmd(paths, cmd);
	
	new_fork = fork();
	if (new_fork < 0)
		perror("Error when forking process");
	else if (new_fork == 0)
		child(&cmds, pipefd, envp, fds);
	return ;
}

void	child(t_cmds *cmds, int *pipefd, char **envp, t_fds fds)
{
	int	fd_in;
	int	fd_out;

	if (fds.in_fd && !fds.out_fd)
		fd_in = fds.in_fd;
	else
		fd_in = pipefd[0];
	if (!fds.in_fd && fds.out_fd)
		fd_out = fds.out_fd;
	else
		fd_out = pipefd[1];
	if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
	{
		big_free(0, cmds);
		return ;
	}
	/* if (fds.in_fd && !fds.out_fd)
		dup2(fds.in_fd, STDIN_FILENO);
	else
		dup2(pipefd[0], STDIN_FILENO);
	if (!fds.in_fd && fds.out_fd)
		dup2(fds.out_fd, STDOUT_FILENO);
	else
		dup2(pipefd[1], STDOUT_FILENO); */
	plug_pipe(pipefd);
	execve((*cmds)->cmd, (*cmds)->cmd_args, envp);
	ft_printf("execve failed.\n");
	return ;
}
