/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:00:15 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/29 11:34:43 by gacorrei         ###   ########.fr       */
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

void	new_process(char *cmd, char **paths, char **envp, t_fds *fds)
{
	int		new_fork;

	get_in_out(fds);
	new_fork = fork();
	if (new_fork < 0)
		perror("Error when forking process");
	else if (new_fork == 0)
		child(cmd, paths, envp, fds);
	return ;
}

/* void	new_process1(char *cmd, char **paths, char **envp, t_fds *fds)
{
	int		new_fork;
	t_cmds	*cmds;

	get_in_out(fds);
	cmds = get_cmd(paths, cmd);
	new_fork = fork();
	if (new_fork < 0)
		perror("Error when forking process");
	else if (new_fork == 0)
		child(&cmds, envp, fds);
	big_free(0, &cmds);
	return ;
}

void	new_process2(char *cmd, char **paths, char **envp, t_fds *fds)
{
	int		new_fork;
	t_cmds	*cmds;

	if ((*fds).flag == 1)
		(*fds).in = (*fds).pipefd1[0];
	else
		(*fds).in = (*fds).pipefd2[0];
	(*fds).out = (*fds).out_fd;
	cmds = get_cmd(paths, cmd);
	new_fork = fork();
	if (new_fork < 0)
		perror("Error when forking process");
	else if (new_fork == 0)
		child(&cmds, envp, fds);
	big_free(0, &cmds);
	return ;
} */

void	child(char *cmd, char **paths, char **envp, t_fds *fds)
{
	t_cmds	*cmds;

	cmds = get_cmd(paths, cmd);
	if (dup2((*fds).in, STDIN_FILENO) < 0
		|| dup2((*fds).out, STDOUT_FILENO) < 0)
		return ;
	plug_pipe(fds->pipefd1);
	plug_pipe(fds->pipefd2);
	execve(cmds->cmd, cmds->cmd_args, envp);
	ft_printf("execve failed.\n");
	big_free(0, &cmds);
	return ;
}
