/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:00:15 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/30 15:52:17 by gacorrei         ###   ########.fr       */
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

/*Input and output file checks*/
int	check_files(char *path1, char *path2)
{
	if (access(path1, F_OK))
		return (ft_printf("Infile can't be accessed.\n"));
	if (access(path1, R_OK))
		return (ft_printf("Infile can't be read.\n"));
	if (access(path2, F_OK))
		return (0);
	if (access(path2, R_OK))
		return (ft_printf("Outfile can't be read.\n"));
	if (access(path2, W_OK))
		return (ft_printf("Outfile can't be written.\n"));
	return (0);
}

/*Creates fork and executes process*/
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

/*Duplicates fd's and executes command*/
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
	{
		big_free(0, &cmds);
		plug_pipes(fds->pipefd1, fds->pipefd2);
		return ;
	}
	plug_pipes(fds->pipefd1, fds->pipefd2);
	execve(cmds->cmd, cmds->cmd_args, envp);
	perror("execve failed.\n");
	big_free(0, &cmds);
	return ;
}
