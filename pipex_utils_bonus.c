/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:00:15 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/04 11:29:25 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Frees double pointer*/
void	free_double(void **array)
{
	int	i;

	i = -1;
	while (array [++i])
		free (array [i]);
	free (array);
	return ;
}

/*Frees everything*/
int	big_free(char **paths, t_cmds **cmds, int **pipefd)
{
	int	i;

	if (paths)
		free_double((void *)paths);
	if (cmds)
	{
		i = -1;
		while ((*cmds)->cmd_args[++i])
			free ((*cmds)->cmd_args[i]);
		free ((*cmds)->cmd_args);
		free ((*cmds)->cmd);
		free((*cmds));
	}
	if (pipefd)
		free_double((void *)pipefd);
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
	int	new_fork;

	get_in_out(fds);
	new_fork = fork();
	if (new_fork < 0)
		perror("Error when forking process");
	else if (new_fork == 0)
		child(cmd, paths, envp, fds);
	fds->i_pipe++;
	return ;
}

/*Duplicates fd's and executes command*/
void	child(char *cmd, char **paths, char **envp, t_fds *fds)
{
	t_cmds	*cmds;

	cmds = get_cmd(paths, cmd);
	if (!cmds->cmd)
	{
		ft_printf("Command not found: %s.\n", cmd);
		big_free(0, &cmds, 0);
		return ;
	}
	if (dup2((*fds).in, STDIN_FILENO) < 0
		|| dup2((*fds).out, STDOUT_FILENO) < 0)
	{
		big_free(0, &cmds, fds->pipefd);
		plug_pipes(fds);
		return ;
	}
	plug_pipes(fds);
	execve(cmds->cmd, cmds->cmd_args, envp);
	perror("execve failed.\n");
	big_free(0, &cmds, fds->pipefd);
	return ;
}
