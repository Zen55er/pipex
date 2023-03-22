/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:58:26 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/21 13:23:17 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	check_args(t_cmds **cmds, char *cmd1, char *cmd2)
{
	(*cmds)->cmd1 = 0;
	(*cmds)->cmd2 = 0;
	(*cmds)->cmd1_args = ft_split(cmd1, " ");
	(*cmds)->cmd2_args = ft_split(cmd2, " ");
	return ;
}

t_cmds	*get_cmds(char **paths, char *cmd1, char *cmd2)
{
	t_cmds	*cmds;
	char	*test1;
	char	*test2;
	int		i;

	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	check_args(&cmds, cmd1, cmd2);
	i = -1;
	while (paths[++i])
	{
		test1 = ft_strjoin(paths[i], cmds->cmd1_args[0]);
		test2 = ft_strjoin(paths[i], cmds->cmd2_args[0]);
		if (!access(test1, F_OK) && !cmds->cmd1)
			cmds->cmd1 = test1;
		else
			free(test1);
		if (!access(test2, F_OK) && !cmds->cmd2)
			cmds->cmd2 = test2;
		else
			free(test2);
		if (cmds->cmd1 && cmds->cmd2)
			break ;
	}
	return (cmds);
}

int	main(int ac, char **av, char **envp)
{
	/* int		pipefd[2];
	int		proc1;
	int		proc2;
	int		infilefd;
	int		outfilefd; */
	char	**paths;
	t_cmds	*cmds;

	if (ac != 5)
		return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile.\n"));
	if (infile_test(av[1]))
		return (1);
	if (outfile_test(av[4]))
		return (1);
	/* infilefd = open(av[1], O_RDONLY);
	outfilefd = open(av[4], O_RDWR); */
	paths = get_path(envp);
	cmds = get_cmds(paths, av[2], av[3]);
	big_free(paths);
	for (int i = 0; cmds[i]; i++)
		ft_printf("Cmds pos %i: %s\n", i, cmds[i]);
	/* pipe(pipefd);
	proc1 = fork;
	if (!proc1)
		child(&pipefd, infilefd, av[2]);
	else
		parent(&pipefd, outfilefd, av[3]);
	close (pipefd[0]);
	close (pipefd[1]); */
	big_free(cmds);
	return (0);
}
