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

/*Gets PATH from envp and adds the required commands at the end*/
t_paths	get_path(char **envp, char *cmd1, char *cmd2)
{
	t_paths	paths;
	int		i;
	char	*temp1;
	char	*temp2;

	i = -1;
	while (envp[++i])
	{
		if (strncmp(envp[i], "PATH", 4))
		{
			paths.paths_cmd1 = ft_split(envp[i], ':');
			paths.paths_cmd2 = ft_split(envp[i], ':');
			break ;
		}
	}
	i = -1;
	while (paths.paths_cmd1[++i])
	{
		temp1 = paths.paths_cmd1[i];
		temp2 = paths.paths_cmd2[i];
		paths.paths_cmd1[i] = ft_strjoin(paths.paths_cmd1[i], cmd1);
		paths.paths_cmd2[i] = ft_strjoin(paths.paths_cmd2[i], cmd2);
		free (temp1);
		free (temp2);
	}
	return (paths);
}

int	main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	int		proc1;
	int		proc2;
	int		infilefd;
	int		outfilefd;
	t_paths	paths;

	if (ac != 5)
		return (ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile.\n"));
	if (infile_test(av[1]))
		return (1);
	if (outfile_test(av[4]))
		return (1);
	infilefd = open(av[1], O_RDONLY);
	outfilefd = open(av[4], O_RDWR);
	paths = get_path(envp, av[2], av[3]);
	for (int i = 0; paths.paths_cmd1[i]; i++)
	{
		ft_printf("Path_cmd1 pos %i: %s\n", i, paths.paths_cmd1[i]);
		ft_printf("Path_cmd2 pos %i: %s\n", i, paths.paths_cmd2[i]);
	}
	pipe(pipefd);
	proc1 = fork;
	if (!proc1)
		child(&pipefd, infilefd, av[2]);
	else
		parent(&pipefd, outfilefd, av[3]);
	close (pipefd[0]);
	close (pipefd[1]);
	big_free(&paths);
	return (0);
}
