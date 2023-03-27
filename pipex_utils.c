/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:00:15 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/27 11:31:02 by gacorrei         ###   ########.fr       */
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

void	new_process(char *cmd, char **paths, char **envp, t_fds fds)
{
	int		pipefd[2];
	int		new_fork;
	t_cmds	*cmds;

	cmds = get_cmd(paths, cmd);
	if (pipe(pipefd) == -1)
		return (ft_printf("Pipe failed\n"));
	new_fork = fork();
	if (new_fork < 0)
		perror("Error when forking process");
	else if (new_fork == 0)
		child(&cmds, pipefd, envp);
	return ;
}

void	child(t_cmds **cmds, int *pipefd, char **envp)
{
	dup2(infilefd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	plug_pipe(pipefd);
	execve(cmds->cmd, cmds->cmd_args, envp);
	ft_printf("execve failed.\n");
	return ;
}
