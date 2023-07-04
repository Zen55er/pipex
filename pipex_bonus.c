/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:24:16 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/04 08:57:25 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Gets PATH from envp and adds '/' at the end*/
char	**get_path(char **envp)
{
	char	**paths;
	int		i;
	char	*temp1;

	i = -1;
	while (envp[++i])
	{
		if (strncmp(envp[i], "PATH", 4) == 0)
			break ;
	}
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		temp1 = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free (temp1);
	}
	return (paths);
}

/*Checks if the given command is in PATH*/
int	check_path(char **paths, char *cmd)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		if (ft_strncmp(paths[i], cmd, ft_strlen(paths[i])) == 0)
			return (1);
	}
	return (0);
}

/*Creates fork and executes process*/
void	new_process(char *cmd, char **paths, char **envp, t_fds *fds)
{
	get_in_out(fds);
	if (fds->in == -1 || fds->fake == 1)
	{
		fds->i_pipe++;
		return ;
	}
	fds->pids[fds->i] = fork();
	if (fds->pids[fds->i] < 0)
		perror("Error when forking process");
	else if (fds->pids[fds->i] == 0)
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
		ft_printf("Command not found: '%s'\n", cmd);
		plug_pipes(fds);
		big_free(0, &cmds, 0, 0);
		fds->fake = 1;
		exit(1);
	}
	if (dup2((*fds).in, STDIN_FILENO) < 0
		|| dup2((*fds).out, STDOUT_FILENO) < 0)
	{
		big_free(0, &cmds, 0, 0);
		exit(1);
	}
	plug_pipes(fds);
	execve(cmds->cmd, cmds->cmd_args, envp);
	perror("execve failed.\n");
	big_free(0, &cmds, fds->pipefd, 0);
	exit(1);
}

int	main(int ac, char **av, char **envp)
{
	t_fds	fds;
	char	**paths;

	if (ac < 5)
		return (ft_printf("Usage: ./pipex infile cmd1 ... cmdn outfile.\n"));
	here_doc(av, &fds);
	if (check_files(&fds, ac, av))
		return (1);
	if (create_pipes(&fds, ac))
		return (2);
	paths = get_path(envp);
	prep_pids(&fds);
	while (++fds.i < ac - 3 - fds.here_doc)
	{
		get_flag(fds.i, ac, &fds);
		new_process(av[fds.i + 2 + fds.here_doc], paths, envp, &fds);
		if (fds.i_pipe > 1)
		{
			close(fds.pipefd[fds.i_pipe - 2][1]);
			close(fds.pipefd[fds.i_pipe - 2][0]);
		}
	}
	big_wait(&fds);
	big_free(paths, 0, fds.pipefd, &fds);
	return (0);
}
