/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:58:26 by gacorrei          #+#    #+#             */
/*   Updated: 2023/03/27 09:48:21 by gacorrei         ###   ########.fr       */
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

t_cmds	*get_cmd(char **paths, char *cmd)
{
	t_cmds	*cmds;
	char	*test;
	int		i;

	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmd = 0;
	cmds->cmd_args = ft_split(cmd, ' ');
	i = -1;
	while (paths[++i])
	{
		test = ft_strjoin(paths[i], cmds->cmd_args[0]);
		if (!access(test, F_OK) && !cmds->cmd)
			cmds->cmd = test;
		else
			free(test);
		if (cmds->cmd)
			break ;
	}
	return (cmds);
}

int	main(int ac, char **av, char **envp)
{
	//int		pipefd[2];
	/*int		proc1;
	int		proc2;
	int		infilefd;
	int		outfilefd; */
	char	**paths;
	t_cmds	*cmds;

	if (ac != 5)
		return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile.\n"));
	/* if (infile_test(av[1]))
		return (1);
	if (outfile_test(av[4]))
		return (1); */
	/* infilefd = open(av[1], O_RDONLY);
	outfilefd = open(av[4], O_RDWR); */
	paths = get_path(envp);
	/* if (pipe(pipefd) == -1)
	{
		big_free(paths, &cmds);
		return (ft_printf("Pipe failed\n"));
	}
	new_process(pipefd, cmds, infilefd, envp);
	plug_pipe(pipefd);
	close(infilefd);
	close(outfilefd); */
	big_free(paths, &cmds);
	return (0);
}
