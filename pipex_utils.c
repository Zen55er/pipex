/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:00:15 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/29 15:03:59 by gacorrei         ###   ########.fr       */
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

int	check_files(char *path1, char *path2)
{
	if (access(path1, F_OK))
		return (ft_printf("Infile can't be accessed.\n"));
	if (access(path1, R_OK))
		return (ft_printf("Infile can't be read.\n"));
	if (access(path2, F_OK))
	{
		ft_printf("Outfile couldn't be accessed. File was created.\n");
		return (0);
	}
	if (access(path2, R_OK))
		return (ft_printf("Outfile can't be read.\n"));
	if (access(path2, W_OK))
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

void	child(char *cmd, char **paths, char **envp, t_fds *fds)
{
	t_cmds	*cmds;

	cmds = get_cmd(paths, cmd);
	if (!cmds->cmd)
	{
		ft_printf("Command not found.\n");
		big_free(0, &cmds);
		plug_pipes(fds->pipefd1, fds->pipefd2);
		return ;
	}
	if (dup2((*fds).in, STDIN_FILENO) < 0
		|| dup2((*fds).out, STDOUT_FILENO) < 0)
		return ;
	plug_pipes(fds->pipefd1, fds->pipefd2);
	execve(cmds->cmd, cmds->cmd_args, envp);
	ft_printf("execve failed.\n");
	big_free(0, &cmds);
	return ;
}
